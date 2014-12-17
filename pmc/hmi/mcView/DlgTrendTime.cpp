// DlgTrendTime.cpp : implementation file
//

#include "stdafx.h"
#include "mcview.h"
#include "DlgTrendTime.h"
#include "DlgTrendComSav.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrendTime dialog


CDlgTrendTime::CDlgTrendTime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrendTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrendTime)
	m_date = COleDateTime::GetCurrentTime();
	m_time = COleDateTime::GetCurrentTime();
	m_mode = 1;
	m_ca1 = FALSE;
	m_ca2 = FALSE;
	m_ca3 = FALSE;
	m_ca4 = FALSE;
	m_ca5 = FALSE;
	m_max1 = 0.0f;
	m_max2 = 0.0f;
	m_max3 = 0.0f;
	m_max4 = 0.0f;
	m_max5 = 0.0f;
	m_min1 = 0.0f;
	m_min2 = 0.0f;
	m_min3 = 0.0f;
	m_min4 = 0.0f;
	m_min5 = 0.0f;
	m_tag1 = _T("");
	m_tag2 = _T("");
	m_tag3 = _T("");
	m_tag4 = _T("");
	m_tag5 = _T("");
	m_autoScale = FALSE;
	m_tag10 = _T("");
	m_tag6 = _T("");
	m_tag7 = _T("");
	m_tag8 = _T("");
	m_tag9 = _T("");
	m_ca10 = FALSE;
	m_ca6 = FALSE;
	m_ca7 = FALSE;
	m_ca8 = FALSE;
	m_ca9 = FALSE;
	m_max10 = 0.0f;
	m_max6 = 0.0f;
	m_max7 = 0.0f;
	m_max8 = 0.0f;
	m_max9 = 0.0f;
	m_min10 = 0.0f;
	m_min6 = 0.0f;
	m_min7 = 0.0f;
	m_min8 = 0.0f;
	m_min9 = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgTrendTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrendTime)
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_date);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_time);
	DDX_CBIndex(pDX, IDC_LENGTH, m_mode);
	DDX_Check(pDX, IDC_CA1, m_ca1);
	DDX_Check(pDX, IDC_CA2, m_ca2);
	DDX_Check(pDX, IDC_CA3, m_ca3);
	DDX_Check(pDX, IDC_CA4, m_ca4);
	DDX_Check(pDX, IDC_CA5, m_ca5);
	DDX_Text(pDX, IDC_MAX1, m_max1);
	DDX_Text(pDX, IDC_MAX2, m_max2);
	DDX_Text(pDX, IDC_MAX3, m_max3);
	DDX_Text(pDX, IDC_MAX4, m_max4);
	DDX_Text(pDX, IDC_MAX5, m_max5);
	DDX_Text(pDX, IDC_MIN1, m_min1);
	DDX_Text(pDX, IDC_MIN2, m_min2);
	DDX_Text(pDX, IDC_MIN3, m_min3);
	DDX_Text(pDX, IDC_MIN4, m_min4);
	DDX_Text(pDX, IDC_MIN5, m_min5);
	DDX_Text(pDX, IDC_TAG1, m_tag1);
	DDV_MaxChars(pDX, m_tag1, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG2, m_tag2);
	DDV_MaxChars(pDX, m_tag2, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG3, m_tag3);
	DDV_MaxChars(pDX, m_tag3, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG4, m_tag4);
	DDV_MaxChars(pDX, m_tag4, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG5, m_tag5);
	DDV_MaxChars(pDX, m_tag5, TAGNAME_TEXT_LENGTH);
	DDX_Check(pDX, IDC_AUTO_SCALE, m_autoScale);
	DDX_Text(pDX, IDC_TAG10, m_tag10);
	DDV_MaxChars(pDX, m_tag10, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG6, m_tag6);
	DDV_MaxChars(pDX, m_tag6, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG7, m_tag7);
	DDV_MaxChars(pDX, m_tag7, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG8, m_tag8);
	DDV_MaxChars(pDX, m_tag8, TAGNAME_TEXT_LENGTH);
	DDX_Text(pDX, IDC_TAG9, m_tag9);
	DDV_MaxChars(pDX, m_tag9, TAGNAME_TEXT_LENGTH);
	DDX_Check(pDX, IDC_CA10, m_ca10);
	DDX_Check(pDX, IDC_CA6, m_ca6);
	DDX_Check(pDX, IDC_CA7, m_ca7);
	DDX_Check(pDX, IDC_CA8, m_ca8);
	DDX_Check(pDX, IDC_CA9, m_ca9);
	DDX_Text(pDX, IDC_MAX10, m_max10);
	DDX_Text(pDX, IDC_MAX6, m_max6);
	DDX_Text(pDX, IDC_MAX7, m_max7);
	DDX_Text(pDX, IDC_MAX8, m_max8);
	DDX_Text(pDX, IDC_MAX9, m_max9);
	DDX_Text(pDX, IDC_MIN10, m_min10);
	DDX_Text(pDX, IDC_MIN6, m_min6);
	DDX_Text(pDX, IDC_MIN7, m_min7);
	DDX_Text(pDX, IDC_MIN8, m_min8);
	DDX_Text(pDX, IDC_MIN9, m_min9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrendTime, CDialog)
	//{{AFX_MSG_MAP(CDlgTrendTime)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_1, On1)
	ON_BN_CLICKED(IDC_2, On2)
	ON_BN_CLICKED(IDC_3, On3)
	ON_BN_CLICKED(IDC_4, On4)
	ON_BN_CLICKED(IDC_5, On5)
	ON_BN_CLICKED(IDC_6, On6)
	ON_BN_CLICKED(IDC_7, On7)
	ON_BN_CLICKED(IDC_8, On8)
	ON_BN_CLICKED(IDC_9, On9)
	ON_BN_CLICKED(IDC_10, On10)
	ON_BN_CLICKED(IDC_DOT, OnDot)
	ON_BN_CLICKED(IDC_SUB, OnSub)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_EN_SETFOCUS(IDC_MAX1, OnSetfocusMax1)
	ON_EN_SETFOCUS(IDC_MAX2, OnSetfocusMax2)
	ON_EN_SETFOCUS(IDC_MAX3, OnSetfocusMax3)
	ON_EN_SETFOCUS(IDC_MAX4, OnSetfocusMax4)
	ON_EN_SETFOCUS(IDC_MAX5, OnSetfocusMax5)
	ON_EN_SETFOCUS(IDC_MIN1, OnSetfocusMin1)
	ON_EN_SETFOCUS(IDC_MIN2, OnSetfocusMin2)
	ON_EN_SETFOCUS(IDC_MIN3, OnSetfocusMin3)
	ON_EN_SETFOCUS(IDC_MIN4, OnSetfocusMin4)
	ON_EN_SETFOCUS(IDC_MIN5, OnSetfocusMin5)
	ON_EN_SETFOCUS(IDC_MAX6, OnSetfocusMax6)
	ON_EN_SETFOCUS(IDC_MAX7, OnSetfocusMax7)
	ON_EN_SETFOCUS(IDC_MAX8, OnSetfocusMax8)
	ON_EN_SETFOCUS(IDC_MAX9, OnSetfocusMax9)
	ON_EN_SETFOCUS(IDC_MAX10, OnSetfocusMax10)
	ON_EN_SETFOCUS(IDC_MIN6, OnSetfocusMin6)
	ON_EN_SETFOCUS(IDC_MIN7, OnSetfocusMin7)
	ON_EN_SETFOCUS(IDC_MIN8, OnSetfocusMin8)
	ON_EN_SETFOCUS(IDC_MIN9, OnSetfocusMin9)
	ON_EN_SETFOCUS(IDC_MIN10, OnSetfocusMin10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrendTime message handlers
extern CMcviewApp theApp;

void CDlgTrendTime::OnSave() 
{
	CFileDialog dlg(false, "tcr", "", OFN_OVERWRITEPROMPT, "tcr Files(*.tcr)|*.tcr||");
	CString sPath = theApp.m_path + "config";
	dlg.m_ofn.lpstrInitialDir = sPath;

	if(dlg.DoModal()==IDOK){
		UpdateData();
		CString strFile = dlg.GetPathName();
		FILE *pConf=fopen(strFile, "w+");
		if(pConf){
			// trend 1
			fprintf(pConf, "%d,", m_ca1);
			fprintf(pConf, "%s,", m_tag1);
			fprintf(pConf, "%g,", m_min1);
			fprintf(pConf, "%g\n", m_max1);
			// trend 2
			fprintf(pConf, "%d,",m_ca2);
			fprintf(pConf, "%s,",m_tag2);
			fprintf(pConf, "%g,", m_min2);
			fprintf(pConf, "%g\n", m_max2);
			// trend 3
			fprintf(pConf, "%d,",m_ca3);
			fprintf(pConf, "%s,",m_tag3);
			fprintf(pConf, "%g,", m_min3);
			fprintf(pConf, "%g\n", m_max3);
			// trend 4
			fprintf(pConf, "%d,",m_ca4);
			fprintf(pConf, "%s,",m_tag4);
			fprintf(pConf, "%g,", m_min4);
			fprintf(pConf, "%g\n", m_max4);
			// trend 5
			fprintf(pConf, "%d,",m_ca5);
			fprintf(pConf, "%s,",m_tag5);
			fprintf(pConf, "%g,", m_min5);
			fprintf(pConf, "%g\n", m_max5);
			// trend 6
			fprintf(pConf, "%d,",m_ca6);
			fprintf(pConf, "%s,",m_tag6);
			fprintf(pConf, "%g,", m_min6);
			fprintf(pConf, "%g\n", m_max6);
			// trend 7
			fprintf(pConf, "%d,",m_ca7);
			fprintf(pConf, "%s,",m_tag7);
			fprintf(pConf, "%g,", m_min7);
			fprintf(pConf, "%g\n", m_max7);
			// trend 8
			fprintf(pConf, "%d,",m_ca8);
			fprintf(pConf, "%s,",m_tag8);
			fprintf(pConf, "%g,", m_min8);
			fprintf(pConf, "%g\n", m_max8);
			// trend 9
			fprintf(pConf, "%d,",m_ca9);
			fprintf(pConf, "%s,",m_tag9);
			fprintf(pConf, "%g,", m_min9);
			fprintf(pConf, "%g\n", m_max9);
			// trend 10
			fprintf(pConf, "%d,",m_ca10);
			fprintf(pConf, "%s,",m_tag10);
			fprintf(pConf, "%g,", m_min10);
			fprintf(pConf, "%g\n", m_max10);

			fclose(pConf);
		}
	}		
}

void CDlgTrendTime::OnLoad()
{
	CDlgTrendComSav dlg;
	dlg.m_dir=theApp.m_path+"config\\*.tcr";

	if(dlg.DoModal()==IDOK){
		CString strFile=theApp.m_path+"config\\"+dlg.m_select+".tcr";
		FILE *pConf = fopen(strFile, "r");
		if(pConf){
			CArgs args;
			char line[1024];
			// 1
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca1 = TRUE;
				}else{
					m_ca1 = FALSE;
				}
				m_tag1 = args.argv[1];
				m_min1 = atof(args.argv[2]);
				m_max1 = atof(args.argv[3]);
			}
			// 2
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca2 = TRUE;
				}else{
					m_ca2 = FALSE;
				}
				m_tag2 = args.argv[1];
				m_min2 = atof(args.argv[2]);
				m_max2 = atof(args.argv[3]);
			}
			// 3
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca3 = TRUE;
				}else{
					m_ca3 = FALSE;
				}
				m_tag3 = args.argv[1];
				m_min3 = atof(args.argv[2]);
				m_max3 = atof(args.argv[3]);
			}
			// 4
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca4 = TRUE;
				}else{
					m_ca4 = FALSE;
				}
				m_tag4 = args.argv[1];
				m_min4 = atof(args.argv[2]);
				m_max4 = atof(args.argv[3]);
			}
			// 5
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca5 = TRUE;
				}else{
					m_ca5 = FALSE;
				}
				m_tag5 = args.argv[1];
				m_min5 = atof(args.argv[2]);
				m_max5 = atof(args.argv[3]);
			}
			// 6
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca6 = TRUE;
				}else{
					m_ca6 = FALSE;
				}
				m_tag6 = args.argv[1];
				m_min6 = atof(args.argv[2]);
				m_max6 = atof(args.argv[3]);
			}
			// 7
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca7 = TRUE;
				}else{
					m_ca7 = FALSE;
				}
				m_tag7 = args.argv[1];
				m_min7 = atof(args.argv[2]);
				m_max7 = atof(args.argv[3]);
			}
			// 8
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca8 = TRUE;
				}else{
					m_ca8 = FALSE;
				}
				m_tag8 = args.argv[1];
				m_min8 = atof(args.argv[2]);
				m_max8 = atof(args.argv[3]);
			}
			// 9
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca9 = TRUE;
				}else{
					m_ca9 = FALSE;
				}
				m_tag9 = args.argv[1];
				m_min9 = atof(args.argv[2]);
				m_max9 = atof(args.argv[3]);
			}
			// 10
			if(NULL != fgets(line,1024,pConf)){
				parse_arg_ey(line,&args,",\n");
				if(0 == strcmp(args.argv[0],"1")){
					m_ca10 = TRUE;
				}else{
					m_ca10 = FALSE;
				}
				m_tag10 = args.argv[1];
				m_min10 = atof(args.argv[2]);
				m_max10 = atof(args.argv[3]);
			}
		}
		UpdateData(FALSE);
	}
}

extern long glRank;
BOOL CDlgTrendTime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN1);
	pBoxOne->SetFocus();
	/*
	CWnd *pWnd = GetDlgItem(IDC_SAVE);;
	if(9 == glRank){
		pWnd->EnableWindow(TRUE);
	}else{
		pWnd->EnableWindow(FALSE); 
	}
	*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDlgTrendTime::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID()==IDC_TAG1){
		pDC->SetTextColor(cuvColor[0]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG2){
		pDC->SetTextColor(cuvColor[1]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG3){
		pDC->SetTextColor(cuvColor[2]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG4){
		pDC->SetTextColor(cuvColor[3]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG5){
		pDC->SetTextColor(cuvColor[4]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG6){
		pDC->SetTextColor(cuvColor[5]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG7){
		pDC->SetTextColor(cuvColor[6]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG8){
		pDC->SetTextColor(cuvColor[7]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG9){
		pDC->SetTextColor(cuvColor[8]);
	}else if(pWnd->GetDlgCtrlID()==IDC_TAG10){
		pDC->SetTextColor(cuvColor[9]);
	}
	
	return hbr;
}

void CDlgTrendTime::On1() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '1',0);		
}

void CDlgTrendTime::On2() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '2',0);	
}

void CDlgTrendTime::On3() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '3',0);	
}

void CDlgTrendTime::On4() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '4',0);	
}

void CDlgTrendTime::On5() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '5',0);	
}

void CDlgTrendTime::On6() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '6',0);		
}

void CDlgTrendTime::On7() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '7',0);	
}

void CDlgTrendTime::On8() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '8',0);		
}

void CDlgTrendTime::On9() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '9',0);	
}

void CDlgTrendTime::On10() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '0',0);	
}

void CDlgTrendTime::OnDot() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '.',0);	
}

void CDlgTrendTime::OnSub() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CHAR, '-',0);	
}

void CDlgTrendTime::OnDel() 
{
	::SendMessage(pBoxOne->m_hWnd, WM_CLEAR , 0, 0);	
}

void CDlgTrendTime::OnSetfocusMax1() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX1);
}

void CDlgTrendTime::OnSetfocusMax2() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX2);
}

void CDlgTrendTime::OnSetfocusMax3() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX3);
}

void CDlgTrendTime::OnSetfocusMax4() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX4);
}

void CDlgTrendTime::OnSetfocusMax5() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX5);
}

void CDlgTrendTime::OnSetfocusMin1() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN1);
}

void CDlgTrendTime::OnSetfocusMin2() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN2);
}

void CDlgTrendTime::OnSetfocusMin3() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN3);
}

void CDlgTrendTime::OnSetfocusMin4() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN4);
}

void CDlgTrendTime::OnSetfocusMin5() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN5);
}

void CDlgTrendTime::OnSetfocusMax6() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX6);
}

void CDlgTrendTime::OnSetfocusMax7() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX7);
}

void CDlgTrendTime::OnSetfocusMax8() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX8);
}

void CDlgTrendTime::OnSetfocusMax9() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX9);
}

void CDlgTrendTime::OnSetfocusMax10() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MAX10);
}

void CDlgTrendTime::OnSetfocusMin6() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN6);
}

void CDlgTrendTime::OnSetfocusMin7() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN7);
}

void CDlgTrendTime::OnSetfocusMin8() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN8);
}

void CDlgTrendTime::OnSetfocusMin9() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN9);
}

void CDlgTrendTime::OnSetfocusMin10() 
{
	pBoxOne = (CEdit*) GetDlgItem(IDC_MIN10);
}
