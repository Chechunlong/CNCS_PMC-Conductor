// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "evtlq.h"
#include "dlgquerybyid.h"
#include "dlgquery.h"
#include "dlgserverip.h"
#include "MainFrm.h"
#include "config.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ALARMPOOL	1024
#define ALARMLEN	1024
typedef CPMCArchive<CPMCEvent, ALARMLEN> CPMCAlarms;

#define OPERATEPOOL 1024
#define OPERATELEN	1024
typedef CPMCArchive<CPMCEvent, OPERATELEN> CPMCOperates;

#define SOEPOOL 1024
#define SOELEN	1024
typedef CPMCArchive<CPMCEvent, SOELEN> CPMCSoes;

CPMCEvent evtsList[MAX_GET_RECORD];
static CPMCAlarms * alarms;
static CPMCOperates * operates;
static CPMCSoes * soes;


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_OPT_QUERY, OnOptQuery)
	ON_COMMAND(ID_OPT_QUERY_BY_ID, OnOptQueryById)
	ON_COMMAND(ID_OPT_IP, OnOptIp)
	ON_COMMAND(ID_OPT_PRINT, OnOptPrint)
	ON_COMMAND(ID_OPT_OUTFILE, OnOptOutfile)
	//}}AFX_MSG_MAP
	ON_NOTIFY(LVN_GETDISPINFO, AFX_IDW_PANE_FIRST, OnGetdispinfoList)
	ON_NOTIFY(NM_CUSTOMDRAW, AFX_IDW_PANE_FIRST, OnDrawList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
static void dumptime(ULONGLONG ull)
{
	SYSTEMTIME tmsys;
	FILETIME tmfile;
	memcpy(&tmfile,&ull,sizeof(ULONGLONG));
	FileTimeToSystemTime(&tmfile,&tmsys);
	char dump[50];
	sprintf(dump,"%d-%d-%d %d:%d:%d\n",tmsys.wYear,tmsys.wMonth,tmsys.wDay,
		tmsys.wHour,tmsys.wMinute,tmsys.wSecond);
}

CMainFrame::CMainFrame()
{
	m_qIniTime=false;
	m_qIniId=false;
}

CMainFrame::~CMainFrame()
{
	WSACleanup();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndView.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT,
	    CRect(0,0,0,0), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create view\n");
		return -1;
	}

	LV_COLUMN listColumn;
    TCHAR*    rgszColumns[] = { _T("序号"),
                                _T("事件")};
    listColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
    listColumn.fmt = LVCFMT_LEFT;
    listColumn.cx = 50;
    listColumn.iSubItem = 0;
    listColumn.pszText = rgszColumns[0];
    m_wndView.InsertColumn(0, &listColumn);
    listColumn.iSubItem = 1;
    listColumn.pszText = rgszColumns[1];
    listColumn.cx = 680;
    m_wndView.InsertColumn(1, &listColumn);

    LV_ITEM listItem;
    listItem.mask = LVIF_TEXT|LVIF_PARAM;
	for(int i = 0; i < MAX_GET_RECORD; i++){
		listItem.iSubItem = 0;
		listItem.iItem = m_wndView.GetItemCount();
		listItem.pszText = LPSTR_TEXTCALLBACK;
		listItem.cchTextMax = 50;
		listItem.lParam = (LPARAM)i;
    
		m_wndView.InsertItem(&listItem);
		m_wndView.SetItemText(listItem.iItem,1, LPSTR_TEXTCALLBACK);
	}
		
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	string str, s1, s2, s3;
	
	//str = string(get_working_dir()) + string("var");
	str = ((CMcEvtQueryApp*)AfxGetApp())->m_folder;
	str += string("/var");
	if(ENOENT == _mkdir(str.c_str())){
		CString msg;
		msg.Format("path %s not found!", str.c_str());
		//msg	= str;
		//msg += " not found!";
		MessageBox(msg);
		PostQuitMessage(0);
	}
	str = str + "/evtd";
	_mkdir(str.c_str());
	s1 = str + "/alarm";
	s2 = str + "/operate";
	s3 = str + "/soe";
	_mkdir( s1.c_str() );
	_mkdir( s2.c_str() );
	_mkdir( s3.c_str() );
	
	alarms = new CPMCAlarms;
	if(alarms){
		alarms->initialize_r(s1.c_str(), ALARMPOOL);
	}

	operates = new CPMCOperates;
	if(operates){
		operates->initialize_r(s2.c_str(), OPERATEPOOL);
	}

	soes = new CPMCSoes;
	if(soes){
		soes->initialize_r(s3.c_str(), SOEPOOL);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_OVERLAPPED | WS_CAPTION
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	HCURSOR hCus=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	HICON hIcn=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,hCus,NULL,hIcn);
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnOptQuery() 
{
	CDlgQuery dlg;
	COleDateTime dt;
	COleDateTime tm;
	PMCSYSTIME tmSys;
	PMCTIME stm, etm;
	if(m_qIniTime){
		dlg.m_date_sta = m_dtSta;
		dlg.m_time_sta = m_dtSta;
		dlg.m_date_end = m_dtEnd;
		dlg.m_time_end = m_dtEnd;
		dlg.m_cur_sel = m_cur_sel;
		dlg.m_filter = m_filter;
	}
	if(dlg.DoModal()==IDOK){
		m_qIniTime=true;

		dt = dlg.m_date_sta;
		tm = dlg.m_time_sta;
		tmSys.year = dt.GetYear();
		tmSys.month = dt.GetMonth();
		tmSys.day = dt.GetDay();
		tmSys.hour = tm.GetHour();
		tmSys.minute = tm.GetMinute();
		tmSys.second = tm.GetSecond();
		tmSys.milliSeconds = 0;
		systm2tm(&tmSys, &stm);
		m_dtSta.SetDateTime(tmSys.year, tmSys.month, tmSys.day,
			tmSys.hour, tmSys.minute, tmSys.second);
		dt=dlg.m_date_end;
		tm=dlg.m_time_end;
		tmSys.year=dt.GetYear();
		tmSys.month=dt.GetMonth();
		tmSys.day=dt.GetDay();
		tmSys.hour=tm.GetHour();
		tmSys.minute=tm.GetMinute();
		tmSys.second=tm.GetSecond();
		tmSys.milliSeconds=0;
		systm2tm(&tmSys, &etm);
		m_dtEnd.SetDateTime(tmSys.year, tmSys.month, tmSys.day,
			tmSys.hour, tmSys.minute, tmSys.second);

		m_cur_sel = dlg.m_cur_sel;
		m_filter = dlg.m_filter;
		m_filter.TrimLeft();
		m_filter.TrimRight();
		
		int count;
		switch(m_cur_sel){
		case 0:
			count = alarms->getRecord_r(stm, etm, MAX_GET_RECORD, evtsList, m_filter);
			break;
		case 1:
			count = operates->getRecord_r(stm, etm, MAX_GET_RECORD, evtsList, m_filter);
			break;
		case 2:
			count = soes->getRecord_r(stm, etm, MAX_GET_RECORD, evtsList, m_filter);
		}
		GetLastError();

		int i;
		for(i = 0; i < MAX_GET_RECORD; i++){
			evtsList[i].valid = false;
		}
		for(i = 0; i < count; i++){
			evtsList[i].valid = true;
		}

		m_wndView.RedrawWindow();
	}
}

void CMainFrame::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	long pt=pDispInfo->item.lParam;
	CPMCEvent *pEvt = &(evtsList[pt]);

	char pc[6];
	sprintf(pc, "%5d", pt + 1);

    if(pDispInfo->item.mask & LVIF_TEXT)
    {
        LPTSTR& pszText = pDispInfo->item.pszText;
        switch(pDispInfo->item.iSubItem)
        {
        case 0:
            pszText = pc;
            break;
        case 1:
			if(pEvt->valid) pszText = pEvt->data;
            break;
        default:
            ASSERT(0);
        }
    }

	*pResult = 0;
}

void CMainFrame::OnDrawList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LPNMLVCUSTOMDRAW pDraw = (LPNMLVCUSTOMDRAW)pNMHDR;

    // Determine the drawing stage.
    DWORD dwDrawStage = pDraw->nmcd.dwDrawStage;
    *pResult = CDRF_NOTIFYITEMDRAW|CDRF_NOTIFYPOSTPAINT|CDRF_NOTIFYPOSTERASE;

    if(dwDrawStage & CDDS_ITEM)
    {
		long pt = pDraw->nmcd.lItemlParam;
		if(pt % 2 == 0){
			pDraw->clrTextBk = RGB(218, 218, 218);
		}
		/*
		CPMCEvent *pEvt = &(evtsList[pt]);
		if(pEvt->valid){
			if(pEvt->eClass == AC_Alarm){
				pDraw->clrText = RGB(255,0,0);
			}else if(pEvt->eClass == AC_CancelAlarm){
				pDraw->clrText = RGB(0,192,0);
			}else if(pEvt->eClass == AC_AckAlarm){
	            pDraw->clrText = RGB(128,128,128);
			}else if(pEvt->eClass == AC_WriteDevice){
	            pDraw->clrText = RGB(0,0,192);
			}
		}
		*/
    }
}

void CMainFrame::OnOptQueryById() 
{
}

void CMainFrame::OnOptIp() 
{
}

void CMainFrame::OnOptOutfile() 
{
    CFileDialog dlg(false, "csv", "", OFN_OVERWRITEPROMPT, "csv Files(*.csv)|*.csv||");
	if(dlg.DoModal()==IDOK){
        CString strFile = dlg.GetPathName();
        FILE *pFile = fopen(strFile, "w+");
        if(pFile){
            CString str;
            str.Format("序号,事件\n");
            fprintf(pFile, "%s", str);
            long id=0;
            while(evtsList[id].valid){
                str.Format("%3d,%s\n", id, evtsList[id].data);
                fprintf(pFile, "%s", str);
                id++;
            }
            fclose(pFile);
        }
    }
}

void CMainFrame::OnOptPrint() 
{
    CPrintDialog dlg(FALSE);
    if(IDOK!=dlg.DoModal()) return;;
    //dlg.GetDefaults();
    
    // is a default printer set up?
    HDC hdcPrinter = dlg.GetPrinterDC();
    if (hdcPrinter == NULL){
        MessageBox("无法找到打印机",NULL,MB_OK|MB_ICONSTOP);
    }else{
        // create a CDC and attach it to the default printer
        CDC dcPrinter;
        dcPrinter.Attach(hdcPrinter);
        
        // call StartDoc() to begin printing
        DOCINFO docinfo;
        memset(&docinfo, 0, sizeof(docinfo));
        docinfo.cbSize = sizeof(docinfo);
        docinfo.lpszDocName = "事件记录报表";
        
        // if it fails, complain and exit gracefully
        if (dcPrinter.StartDoc(&docinfo) < 0){
            MessageBox("无法初始化打印机",NULL,MB_OK|MB_ICONSTOP);
        }else{
            dcPrinter.SetMapMode(MM_TWIPS);
            CFont *pOldFont;
            CFont fnt;
            if(fnt.CreatePointFont(100,"宋体",&dcPrinter)){
                pOldFont=(CFont*)dcPrinter.SelectObject(&fnt);                  
            }else{
                pOldFont=(CFont*)dcPrinter.SelectStockObject(DEVICE_DEFAULT_FONT);
            }
            CPoint pt(dcPrinter.GetDeviceCaps(HORZRES),dcPrinter.GetDeviceCaps(VERTRES));
            dcPrinter.DPtoLP (&pt);
            pt.y=-pt.y;
            CSize sz=dcPrinter.GetTextExtent("序号  ");
            int lineHeight=sz.cy*1.5;
            int lineCount=(pt.y-sz.cy*10)/lineHeight;
            if(lineCount<0) return;
            long id=0;
            CString str;
            int i,iPage=0;
            int cLeftGap=800;
            while(evtsList[id].valid){
                // start a page
                if (dcPrinter.StartPage() < 0){
                    MessageBox("无法初始化页",NULL,MB_OK|MB_ICONSTOP);
                    dcPrinter.AbortDoc();
                }else{
                    // actually do some printing
                    //print title
                    iPage++;
                    str.Format("事件记录报表 第%2d页",iPage);
                    dcPrinter.TextOut(cLeftGap,-lineHeight*3,str);
                    str.Format("序号  事件");
                    dcPrinter.TextOut(cLeftGap,-lineHeight*5,str);
                    for(i=0;i<lineCount;i++){
                        if(evtsList[id].valid){
                            str.Format("%3d",id);
                            dcPrinter.TextOut(cLeftGap,-lineHeight*(6+i),str);
                            str.Format("%s",evtsList[id].data);
                            dcPrinter.TextOut(cLeftGap+sz.cx,-lineHeight*(6+i),str);
                            id++;
                        }else{
                            break;
                        }
                    }
                }
                dcPrinter.EndPage();
            }
            dcPrinter.SelectObject(pOldFont);
            dcPrinter.EndDoc();
        }
    }
}
