// mcviewDlg.cpp : implementation file
//

#include "stdafx.h"
#pragma hdrstop
#include "mcview.h"
#include "mcviewDlg.h"
#include "fview.h"
#include "diainputd.h"
#include "diainputa.h"
#include "diaalarmlist.h"
#include "diasystem.h"
#include "dlgloop.h"
#include <hisproxy.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFView theView;
long glViewWidth,glViewHeight;
long glTimer;
HICON ghNA;
long glRank;
CDiaInputD gDiaInputD;
CDiaInputA gDiaInputA;

/////////////////////////////////////////////////////////////////////////////
// CMcviewDlg dialog

void CDECL AlarmCallBack(int rank, ALARM_CLASS ac, const char *msg, PCRTK_ADDR)
{
	if(!g_bShowAllAlarms && rank < 500){
		return;
	}
	CAlarmRecord alarm;
	alarm.m_ac=ac;
	alarm.m_rank=rank;
	strncpy(alarm.m_msg,msg,sizeof(alarm.m_msg));
	alarm.m_msg[sizeof(alarm.m_msg) - 1] = 0;
	alarm.m_valid=true;
	g_AlarmQueueTail++;
	if(g_AlarmQueueTail == RCT_ALARM_COUNT){
		g_AlarmQueueTail = 0;
	}
	g_AlarmRecords[g_AlarmQueueTail] = alarm;

	CMcviewDlg *pCtlDlg=(CMcviewDlg*)(((CMcviewApp*)::AfxGetApp())->GetMainWnd());
	if(!pCtlDlg) return;

	CString sAlarm;
	g_TopAlarmPt = FindTopAlarm();
	if(g_TopAlarmPt >= 0){
		sAlarm.Format("%s", g_AlarmRecords[g_TopAlarmPt].m_msg);
		pCtlDlg->SetDlgItemText(IDC_ALARM,sAlarm);
	}
}

static void _cdecl _OnProgress(__uint t, __uint c, const char * msg)
{
}

CMcviewDlg::CMcviewDlg(UINT nID, CWnd* pParent /*=NULL*/)
	: CDialog(nID, pParent)
{
	//{{AFX_DATA_INIT(CMcviewDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_brushWhite.CreateSolidBrush(RGB(255,255,255));
	glRank=0;
	// alarm_callback=AlarmCallBack;
	g_AlarmQueueTail=-1;
	g_TopAlarmPt=-1;
	m_curView=-1;
	for(int i=0;i<10;i++){
		m_viewList[i].Empty();
	}

	m_loopCount = 0;
	m_loopCurrent = 0;
	m_loopInterval = 3;
	m_bShowLoop = false;
}

CMcviewDlg::~CMcviewDlg()
{
	POSITION pos;
	for(pos=m_PopViews.GetHeadPosition();pos!=NULL;){
		delete m_PopViews.GetNext(pos);
	}	 
	m_PopViews.RemoveAll();
	uninitHisProxy();
	uninit_proxy();
}

void CMcviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMcviewDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMcviewDlg, CDialog)
	//{{AFX_MSG_MAP(CMcviewDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SYSTEM, OnSystem)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ACKALARM, OnAckalarm)
	ON_BN_CLICKED(IDC_ALARMLIST, OnAlarmlist)
	ON_BN_CLICKED(IDC_INDEX, OnIndex)
	ON_BN_CLICKED(IDC_NOW, OnNow)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_ALARM, OnAlarm)
	ON_BN_CLICKED(IDC_KEY, OnKey)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_LOOP, OnLoop)
	ON_WM_DESTROY()
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMcviewDlg message handlers

BOOL CMcviewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	init_proxy(
		m_hWnd, 
		PROXY_ENABLE_BGLOADER | PROXY_ENABLE_DISPATCHER
		);
	initHisProxy();

	// Set the icon for this dialog.  The framework does this automatically
	//	when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// name self, so that the successively coming instances
	// will find this window
	SetWindowText(MCVIEW_MAIN_DLG_NAME);

	// 设置控制板为全窗口宽，高度为全窗口宽的1/32
	RECT rectDesktop;
	::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
	int iW=rectDesktop.right;
	SetWindowPos(NULL,0,rectDesktop.bottom-iW/32,iW,iW/32,0);
	
	glTimer=0;
	ghNA=((CMcviewApp*)::AfxGetApp())->LoadIcon(IDI_NA);
	//显示窗口
	glViewWidth=iW;
	glViewHeight=rectDesktop.bottom-iW/32;
	theView.m_pCtrDlg=this;
	theView.Create(IDD_FVIEW_DIALOG);
	theView.MoveWindow(0,0,glViewWidth,glViewHeight);
	theView.ShowWindow(SW_SHOWNORMAL);
 
	//设置控件位置
	GetClientRect(&rectDesktop);
	//ClientToScreen(&rectDesktop);
	iW=rectDesktop.right-rectDesktop.left;
	int iH=rectDesktop.bottom-rectDesktop.top;
	CWnd* pContrl;
	//system button
	pContrl=GetDlgItem(IDC_SYSTEM);
	pContrl->MoveWindow(0,0,iW/24,iH);
	//key
	pContrl=GetDlgItem(IDC_KEY);
	pContrl->MoveWindow(iW-5*iW/24-iW/2-iW/6-2*iW/36,0,iW/24,iH);
	//index
	pContrl=GetDlgItem(IDC_INDEX);
	pContrl->MoveWindow(iW-4*iW/24-iW/2-iW/6-2*iW/36,0,iW/24,iH);
	//previous
	pContrl=GetDlgItem(IDC_PREVIOUS);
	pContrl->MoveWindow(iW-3*iW/24-iW/2-iW/6-2*iW/36,0,iW/36,iH);
	//next 
	pContrl=GetDlgItem(IDC_NEXT);
	pContrl->MoveWindow(iW-3*iW/24-iW/2-iW/6-iW/36,0,iW/36,iH);
	//loop
	pContrl=GetDlgItem(IDC_LOOP);
	pContrl->MoveWindow(iW-3*iW/24-iW/2-iW/6,0,iW/24,iH);
	//time lab
	pContrl=GetDlgItem(IDC_TIME);
	pContrl->MoveWindow(iW-2*iW/24-iW/2-iW/6,0,iW/6,iH);
	//alarm
	pContrl=GetDlgItem(IDC_ALARM);
	pContrl->MoveWindow(iW-2*iW/24-iW/2,0,iW/2,iH);
	//ack alarm
	pContrl=GetDlgItem(IDC_ACKALARM);
	pContrl->MoveWindow(iW-2*iW/24,0,iW/24,iH);
	//alarm list
	pContrl=GetDlgItem(IDC_ALARMLIST);
	pContrl->MoveWindow(iW-iW/24,0,iW/24,iH);
	
	//设置定时器
	m_nTimerRefresh=SetTimer(1,250,0);

	m_curView=0;

	m_viewList[m_curView] = g_startFile;
	theView.LoadFile(g_startFile);

	if(g_bEnableNoSwitch){
		SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	}

	g_ProxyDispatchTable.OnAlarm = AlarmCallBack;
	g_ProxyDispatchTable.OnProgress = _OnProgress;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//	to draw the icon.  For MFC applications using the document/view model,
//	this is automatically done for you by the framework.

void CMcviewDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	static bFirst=true;
	if(bFirst) theView.SetFocus();
	bFirst=false;
}

// The system calls this to obtain the cursor to display while the user drags
//	the minimized window.
HCURSOR CMcviewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMcviewDlg::OnSystem() 
{
	CDiaSystem dlg(&theView);
	dlg.m_rank=glRank;
	int iRet=dlg.DoModal();
	glRank=dlg.m_rank;
	if(IDC_RETURN_WND==iRet){
		theView.cleanView();
		CDialog::OnCancel();	
	}

	theView.SetFocus();
}

void CMcviewDlg::OnCancel() 
{
}

HBRUSH CMcviewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		
	if(pWnd->GetDlgCtrlID()==IDC_ALARM){		
		// Set the text color to red.
		if(g_TopAlarmPt>=0){
			if(g_AlarmRecords[g_TopAlarmPt].m_ac==AC_Alarm){
				pDC->SetTextColor(RGB(255, 0, 0));
			}else if(g_AlarmRecords[g_TopAlarmPt].m_ac==AC_WriteDevice){
				pDC->SetTextColor(RGB(0, 0, 255));
			}else{
				pDC->SetTextColor(RGB(0,192,0));
			}
		}

		// Set the background mode for text to transparent 
		// so background will show thru.
		pDC->SetBkMode(TRANSPARENT);

		// Return handle to our CBrush object.
		//hbr = m_brush;
		hbr=m_brushWhite;
	}

	return hbr;
}

class CAutoPopup
{
public:

#define popupWhenVariableIsOn 1
#define popupAutoHide 2
#define popupOverlay 4
#define maxPopups 64

	struct popupEntry_t{
		TAG_NAME tn;
		__int flags;
		char associatedPicture[MAX_PATH];
	};

	__uint nEntries;
	popupEntry_t entries[maxPopups];

	void init();
	void run();
};

void CAutoPopup::init()
{
	__uint i;
	popupEntry_t * ent;

	nEntries = (__uint)GetPrivateProfileInt(
		"AutoPopup",
		"count",
		0,
		get_config_file()
		);
	if(nEntries >= maxPopups){
		nEntries = maxPopups;
	}
	ent = entries;
	char lineBuf[1024];
	char key[4];
	memset(&entries, 0, sizeof(entries));
	for(i=0; i<nEntries; i++){
		sprintf(key, "%d", i);
		GetPrivateProfileString(
			"AutoPopup",
			key,
			"",
			lineBuf,
			sizeof(lineBuf),
			get_config_file()
			);
		CArgs a;
		parse_arg_ex(lineBuf, &a, ",");
		if(a.argc != 5){
			continue;
		}
		if(!tagname_by_text(&ent->tn, a.argv[0])){
			continue;
		}
		if(atoi(a.argv[1])){
			ent->flags |= popupWhenVariableIsOn;
		}
		if(atoi(a.argv[2])){
			ent->flags |= popupOverlay;
		}
		if(atoi(a.argv[3])){
			ent->flags |= popupAutoHide;
		}
		strncpy(ent->associatedPicture, a.argv[4], MAX_PATH);
		ent->associatedPicture[MAX_PATH - 1] = 0;
		ent++;
	}
	nEntries = ent - entries;
}

CAutoPopup autoPopups;

void CMcviewDlg::doAutoPopup()
{
	// 2004/5/30, auto-popups
	do{
		__uint i;
		static bool bPopupInited;
		CAutoPopup::popupEntry_t * ent;
		
		if(!bPopupInited){
			autoPopups.init();
			bPopupInited = true;
		}
		ent = autoPopups.entries;
		if(!lock_rtdb(__false, 1000)){
			break;
		}
		for(i=0; i<autoPopups.nEntries; i++, ent++){
			//
			PCRTK_TAG tag;
			bool bPopup;
			
			tag = query_tag_f(&ent->tn);
			if(!tag){
				continue;
			}
			if(get_value_type(tag->s.Flags) != dt_bool){
				continue;
			}
			bPopup = tag->d.Value.Value.b? true : false;
			if(!(ent->flags & popupWhenVariableIsOn)){
				bPopup = !bPopup;
			}
			if(bPopup){
				if(ent->flags & popupOverlay){
					theView.LoadFile(ent->associatedPicture);
				}else{
					PopupView(ent->associatedPicture);
				}
			}else{
				if((ent->flags & popupAutoHide) && !(ent->flags & popupOverlay)){
					CFView * view;
					view = FindView(ent->associatedPicture);
					if(view){
						view->CloseWindow();
					}
				}
			}
		}
		unlock_rtdb();
	}while(0);
}

void CMcviewDlg::soundAlarm()
{
	if(g_AlarmQueueTail < 0){
		// no alarms
		return;
	}
	int i;
	CAlarmRecord * p = g_AlarmRecords;
	bRaiseSoundAlarm = false;
	for(i=0; i<RCT_ALARM_COUNT;i++, p++){
		if(p->m_valid && !(p->m_ac==AC_CancelAlarm) && !p->m_ack
			&&
			p->m_rank > 500
		){
			bRaiseSoundAlarm = true;
			return;
		}
	}
}

void CMcviewDlg::OnTimer(UINT nIDEvent) 
{
	static int iCount=0;

	if(nIDEvent == 1){
		glTimer++;

		//refresh HMI every 100 ms
		theView.Show();
		CFView* pPopView;
		POSITION pos;

		for(pos=m_PopViews.GetHeadPosition();pos!=NULL;){
			pPopView=(CFView*)(m_PopViews.GetNext(pos));
			pPopView->Show();
		}

		//refresh digital input dialog if exist
		if(gDiaInputD.m_bVisible) gDiaInputD.RefreshShow();

		//refresh analog input dialog if exist
		if(gDiaInputA.m_bVisible) gDiaInputA.RefreshShow();

		//refresh time every 250 ms
		if(iCount%4==0){
			GetLocalTime(&m_current);
			CString sCurrent;
			sCurrent.Format("%4d年%02d月%02d日 %02d:%02d:%02d",m_current.wYear,m_current.wMonth,
				m_current.wDay,m_current.wHour,m_current.wMinute,m_current.wSecond);
			SetDlgItemText(IDC_NOW,sCurrent);
		}
		if(iCount % 20 == 0 && bEnableSoundAlarm){
			// beep every 5 seconds
			soundAlarm();
		}
		iCount++;

		doAutoPopup();
	}else if(nIDEvent == 2){
		theView.LoadFile(m_viewLoop[m_loopCurrent]);
		m_loopCurrent++;
		if(m_loopCurrent >= m_loopCount){
			m_loopCurrent = 0;
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CMcviewDlg::OnAckalarm() 
{
	if(g_TopAlarmPt<0) {
		return;
	}
	g_AlarmRecords[g_TopAlarmPt].m_ack=true;

	// ok, advance g_TopAlarmPt to next un-confirmed
	// alarm entry
	g_TopAlarmPt = FindTopAlarm();

	if(g_TopAlarmPt>=0){
		// update the list-box
		CString sAlarm;
		sAlarm.Format("%s",g_AlarmRecords[g_TopAlarmPt].m_msg);
		SetDlgItemText(IDC_ALARM,sAlarm);
	}else{
		SetDlgItemText(IDC_ALARM,"");
	}
}

void CMcviewDlg::OnAlarmlist() 
{
	static CDiaAlarmList dlg(&theView);
	
	if(!dlg.m_hWnd){
		dlg.Create(IDD_ALARMLIST, &theView);
	}
	
	dlg.UpdateList();
	dlg.ShowWindow(SW_SHOWNORMAL);

	/*
	// dlg.DoModal();
	for(i=0;i<RCT_ALARM_COUNT;i++){
		g_AlarmRecords[i].m_inlist=false;
	}
	*/
	if(g_TopAlarmPt < 0) {
		return;
	}
	if(g_AlarmRecords[g_TopAlarmPt].m_ack) {
		OnAckalarm();
	}
}

void CMcviewDlg::OnIndex() 
{
	m_curView++;
	if(m_curView>9) m_curView=0;
	m_viewList[m_curView]="index.gdf";
	theView.LoadFile("index.gdf");
	theView.LoadFile("index.gdf");
	theView.SetFocus();
}

void CMcviewDlg::OnOK() 
{
	//do nothing	
	//CDialog::OnOK();
}

void CMcviewDlg::OnNow() 
{
	theView.SetFocus();	
}

void CMcviewDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	theView.SetFocus();	
	CDialog::OnLButtonUp(nFlags, point);
}

void CMcviewDlg::OnAlarm() 
{
	theView.SetFocus();	
}

void CMcviewDlg::OnKey() 
{
	theView.SetFocus();	
}

void CMcviewDlg::OnPrevious() 
{
	for(int i=0;i<10;i++){
		m_curView--;
		if(m_curView<0) m_curView=9;
		if(!m_viewList[m_curView].IsEmpty()){
			theView.LoadFile(m_viewList[m_curView]);
			break;
		}
	}
	theView.SetFocus();		
}

void CMcviewDlg::OnNext() 
{
	for(int i=0;i<10;i++){
		m_curView++;
		if(m_curView>9) m_curView=0;
		if(!m_viewList[m_curView].IsEmpty()){
			theView.LoadFile(m_viewList[m_curView]);
			break;
		}
	}
	theView.SetFocus();		
}


CFView * CMcviewDlg::FindView(CString sFileName)
{
	CFView* pPopView;
	POSITION pos;
	for(pos=m_PopViews.GetHeadPosition();pos!=NULL;){
		pPopView=(CFView*)(m_PopViews.GetNext(pos));
		//pPopView->Show();
		if(pPopView->m_sFileName==sFileName){
			//pPopView->ShowWindow(SW_SHOW);
			return pPopView;
		}
	}
	return NULL;
}

void CMcviewDlg::PopupView(CString sFileName,int x,int y)
{
	CFView* pPopView;

	pPopView = FindView(sFileName);

	if(pPopView){
		pPopView->SetFocus();
		return;
	}

	pPopView = new (CFView);
	//CFPopView *pPopView=new(CFPopView);
	pPopView->m_pCtrDlg = this;
	pPopView->m_bPopup = true;
	pPopView->Create(IDD_POPUP, &theView);
	pPopView->LoadFile(sFileName, x, y);
	
	// 2003/7/9 Jackie
	theView.PlaceWindowAt(pPopView, x, y);

	pPopView->ShowWindow(SW_SHOW);
	pPopView->m_pos = m_PopViews.AddTail(pPopView);
	pPopView = NULL;

	CloseOldPopView();
}

void CMcviewDlg::RemovePopView(POSITION pos)
{
	m_PopViews.RemoveAt(pos);
}

void CMcviewDlg::OnLoop() 
{
	// test code for bug-2003-7-19
	// TerminateProcess(GetCurrentProcess(), 0);
	// no use, not caused by this
	
	theView.SetFocus();		
	CWnd *pWndLoop = GetDlgItem(IDC_LOOP);

	if(m_bShowLoop){
		m_bShowLoop = false;
		KillTimer(2);
		pWndLoop->SetWindowText("循环");
		return;
	}

	CDlgLoop dlgLoop;
	dlgLoop.m_interval = m_loopInterval;

	if(dlgLoop.DoModal() != IDOK){
		return;
	}
	
	m_loopCurrent = 0;
	m_loopCount = 0;

	CString sLoopFile = ((CMcviewApp*)::AfxGetApp())->m_path+"loops";
	FILE *pLoops = fopen((LPCTSTR)sLoopFile, "r");
	ASSERT(pLoops != NULL);
	CString sItem;
	char buf[1024];
	while(fgets(buf, 1024, pLoops)){
		sItem = buf;
		sItem.Remove(10);
		sItem.Remove(13);
		m_viewLoop[m_loopCount] = sItem + ".gdf";
		m_loopCount++;
		if(m_loopCount >= 32){
			break;
		}
	}
	fclose(pLoops);

	if(m_loopCount < 2){
		return;
	}
	m_loopInterval = dlgLoop.m_interval;

	m_bShowLoop = true;
	SetTimer(2, m_loopInterval * 1000, NULL);
	pWndLoop->SetWindowText("停止");

	theView.LoadFile(m_viewLoop[m_loopCurrent]);
	m_loopCurrent++;
	if(m_loopCurrent >= m_loopCount){
		m_loopCurrent = 0;
	}
}

void CMcviewDlg::OnDestroy() 
{
	g_ProxyDispatchTable.OnAlarm = 0;
	// TODO: Add your message handler code here	
}

BOOL CMcviewDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	mcview_ext_cmd_t * cmd;
	cmd = (mcview_ext_cmd_t * )pCopyDataStruct->lpData;
	if(pCopyDataStruct->cbData == sizeof(*cmd)){
		set_working_dir(cmd->projDir);
		theApp.m_path = cmd->projDir;
		theView.LoadFile(cmd->fileName);
	}
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}


void CMcviewDlg::PopupTrend(CString tag1, CString tag2, CString tag3, CString tag4, CString tag5)
{
	CFView* pPopView;

	pPopView = new (CFView);
	pPopView->m_pCtrDlg = this;
	pPopView->m_bPopup = true;
	pPopView->Create(IDD_POPUP,&theView);
	pPopView->LoadFile("DEF_TREND.gdf",0,0);
	pPopView->setTrendTags(tag1, tag2, tag3, tag4, tag5);

	RECT rectDesktop;
	::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
	theView.PlaceWindowAt(pPopView, rectDesktop.right / 2, 0);

	pPopView->ShowWindow(SW_SHOW);
	pPopView->m_pos=m_PopViews.AddTail(pPopView);
	pPopView=NULL;

	CloseOldPopView();
}

void CMcviewDlg::CloseOldPopView()
{
	while(m_PopViews.GetCount() > g_maxPopup){
		CFView* pPopView;
		pPopView = (CFView*)m_PopViews.GetHead();
		m_PopViews.RemoveHead();
		pPopView->DestroyWindow();
		delete pPopView;
	}
}
