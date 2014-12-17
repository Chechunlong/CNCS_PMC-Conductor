// DiaSystem.cpp : implementation file
//
#include "stdafx.h"
#include "mcview.h"
#include "DiaSystem.h"
#include "DiaPassword.h"
#include "fview.h"
#include "dlgabout.h"
#include "keyhook.h"
#include "shellapi.h"

#include "rtkgui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiaSystem dialog
extern CFView theView;
//extern HHOOK hKeyboardLL;
extern BOOL gbNoSwitch;

CDiaSystem::CDiaSystem(CWnd* pParent /*=NULL*/)
	: CDialog(CDiaSystem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiaSystem)
	m_rank = 0;
	m_noSwitch = FALSE;
	//}}AFX_DATA_INIT
	for(int i=0;i<10;i++){
		m_password[i].Empty();
	}
	LoadPassword();

	m_noSwitch=gbNoSwitch;
	//if(NULL!=hKeyboardLL) m_noSwitch = TRUE;
}


void CDiaSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiaSystem)
	DDX_Control(pDX, IDC_SW2, m_sw2);
	DDX_Radio(pDX, IDC_RANK0, m_rank);
	DDX_Check(pDX, IDC_NOSWITCH, m_noSwitch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiaSystem, CDialog)
	//{{AFX_MSG_MAP(CDiaSystem)
	ON_BN_CLICKED(IDC_RANK0, OnRank0)
	ON_BN_CLICKED(IDC_RANK1, OnRank1)
	ON_BN_CLICKED(IDC_RANK2, OnRank2)
	ON_BN_CLICKED(IDC_RANK3, OnRank3)
	ON_BN_CLICKED(IDC_RANK4, OnRank4)
	ON_BN_CLICKED(IDC_RANK5, OnRank5)
	ON_BN_CLICKED(IDC_RANK6, OnRank6)
	ON_BN_CLICKED(IDC_RANK7, OnRank7)
	ON_BN_CLICKED(IDC_RANK8, OnRank8)
	ON_BN_CLICKED(IDC_RANK9, OnRank9)
	ON_BN_CLICKED(IDC_RETURN_WND, OnReturnWnd)
	ON_BN_CLICKED(IDC_CHG_PWD, OnChgPwd)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_NOSWITCH, OnNoswitch)
	ON_WM_KEYDOWN()
	ON_WM_CHARTOITEM()
	ON_WM_CHAR()
	ON_LBN_DBLCLK(IDC_SW2, OnDblclkSw2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiaSystem message handlers

void CDiaSystem::OnCancel() 
{
	return;
	
	CDialog::OnCancel();
}

void CDiaSystem::OnRank0() 
{
	SetDlgItemText(IDC_ERR,"");
	SetDlgItemText(IDC_PWD,"");
	m_rank=0;
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank1() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<1){
		if(0==m_password[1].Compare(sPwd)){
			m_rank=1;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=1;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank2() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<2){
		if(0==m_password[2].Compare(sPwd)){
			m_rank=2;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=2;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank3() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<3){
		if(0==m_password[3].Compare(sPwd)){
			m_rank=3;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=3;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank4() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<4){
		if(0==m_password[4].Compare(sPwd)){
			m_rank=4;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=4;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank5() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<5){
		if(0==m_password[5].Compare(sPwd)){
			m_rank=5;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=5;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank6() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<6){
		if(0==m_password[6].Compare(sPwd)){
			m_rank=6;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=6;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank7() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<7){
		if(0==m_password[7].Compare(sPwd)){
			m_rank=7;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=7;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank8() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<8){
		if(0==m_password[8].Compare(sPwd)){
			m_rank=8;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=8;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

void CDiaSystem::OnRank9() 
{
	CString sPwd;
	GetDlgItemText(IDC_PWD,sPwd);

	SetDlgItemText(IDC_ERR,"");
	if(m_rank<9){
		if(0==m_password[9].Compare(sPwd)){
			m_rank=9;
		}else{
			SetDlgItemText(IDC_ERR,"¿ÚÁî´íÎó");
		}
	}else{
		m_rank=9;
	}
	SetDlgItemText(IDC_PWD,"");
	
	UpdateData(FALSE);
	SetButton();
}

extern CMcviewApp theApp;
BOOL CDiaSystem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// load sw2 app
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	CString sTemp;
	CString sPath;
	sPath = theApp.m_path + "sw2\\*.lnk";
	hFind = FindFirstFile((LPCTSTR)sPath, &FindFileData);
	if(hFind!=INVALID_HANDLE_VALUE){
		sTemp=FindFileData.cFileName;
		sTemp=sTemp.Left(sTemp.GetLength()-4);
		m_sw2.AddString(sTemp);
		while(FindNextFile(hFind,&FindFileData)){
			sTemp=FindFileData.cFileName;
			sTemp=sTemp.Left(sTemp.GetLength()-4);
			m_sw2.AddString(sTemp);
		}
		FindClose(hFind);
	}

	SetButton();
		
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDiaSystem::SetButton()
{
	BOOL en;
	if(m_rank<9) en=FALSE;
	else en=TRUE;

	CWnd *pwnd;
	pwnd=GetDlgItem(IDC_RETURN_WND);
	pwnd->EnableWindow(en);
	pwnd=GetDlgItem(IDC_CHG_PWD);
	pwnd->EnableWindow(en);
	pwnd=GetDlgItem(IDC_PRINT);
	pwnd->EnableWindow(m_rank >=0? TRUE : FALSE);
	pwnd=GetDlgItem(IDC_NOSWITCH);
	pwnd->EnableWindow(en);
	pwnd=GetDlgItem(IDC_SW2);
	pwnd->EnableWindow(en && !m_noSwitch);
}

void CDiaSystem::OnReturnWnd() 
{
	EndDialog(IDC_RETURN_WND);
}

void CDiaSystem::OnChgPwd() 
{
	CDiaPassword dlg;
	if(dlg.DoModal()==IDOK){
		m_password[dlg.m_rank]=dlg.m_pwd;
		SavePassword();
	}
}

void CDiaSystem::LoadPassword()
{
	CString sKeyFile=((CMcviewApp*)::AfxGetApp())->m_path+"keys";
	FILE *pKeys=fopen((LPCTSTR)sKeyFile,"rb");
	char cKey[17];
	if(NULL!=pKeys){
		for(int i=0;i<10;i++){
			fread(cKey,17,1,pKeys);
			m_password[i].Format("%s",cKey);
		}
		fclose(pKeys);
	}
}

void CDiaSystem::SavePassword()
{
	CString sKeyFile=((CMcviewApp*)::AfxGetApp())->m_path+"keys";
	FILE *pKeys=fopen((LPCTSTR)sKeyFile,"wb");
	char cKey[27];
	if(NULL!=pKeys){
		for(int i=0;i<10;i++){
			strncpy(cKey,(LPCTSTR)m_password[i],16);
			fwrite(cKey,17,1,pKeys);
		}
		fclose(pKeys);
	}
}

void CDiaSystem::OnPrint() 
{
	theView.PrintView();
}  

void CDiaSystem::OnAbout() 
{
#if 0
	CDlgAbout dlg;
	dlg.DoModal();
#else
	pmcAbout(m_hWnd, "ÔËÐÐ»­Ãæ");
#endif
}

void CDiaSystem::OnNoswitch() 
{
	if(!g_bEnableNoSwitch){
		return;
	}
	UpdateData(TRUE);
	CFView* pTheView=(CFView*)GetParent();

	char sysdir[_MAX_PATH];
	::GetSystemDirectory(sysdir,_MAX_PATH);
	CString sGina;
	sGina.Format("%s\\pmcgina.cf",sysdir);
	FILE *fGina=fopen((LPCTSTR)sGina,"wb");

	CWnd *pSw2 = GetDlgItem(IDC_SW2);

	gbNoSwitch=m_noSwitch;
	if(m_noSwitch){
		//hKeyboardLL=SetWindowsHookEx(WH_KEYBOARD_LL,
		//	  (HOOKPROC)LowLevelKeyboardProc,::AfxGetApp()->m_hInstance,0);
		if(NULL!=pTheView) pTheView->m_pCtrDlg->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		if(NULL!=fGina){
			int b=1;
			fwrite(&b,sizeof(int),1,fGina);
			fclose(fGina);
		}
		pSw2->EnableWindow(FALSE);
	}else{
		//if(NULL!=hKeyboardLL) UnhookWindowsHookEx(hKeyboardLL);
		//hKeyboardLL=NULL;
		if(NULL!=pTheView) pTheView->m_pCtrDlg->SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		if(NULL!=fGina){
			int b=0;
			fwrite(&b,sizeof(int),1,fGina);
			fclose(fGina);
		}
		pSw2->EnableWindow();
	}
}

void CDiaSystem::OnDblclkSw2() 
{
	CString strExe;
	int nSel = m_sw2.GetCurSel();
	if(LB_ERR != nSel){
		m_sw2.GetText(nSel, strExe);
		strExe = theApp.m_path + "sw2\\" + strExe + ".lnk";
		int hRtv = (int)ShellExecute(theApp.m_pMainWnd->m_hWnd, NULL, strExe, NULL, NULL, SW_SHOWNORMAL);
		if(hRtv > 32){
			EndDialog(IDOK);
		}else{
			CString sErr;
			sErr.Format("Can't launch %s, err code:%d.", strExe, hRtv);
			MessageBox(sErr,NULL,MB_OK | MB_ICONSTOP);
		}
	}
}
