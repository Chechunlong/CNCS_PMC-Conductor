// DiaInputD.cpp : implementation file
//

#include "stdafx.h"
#include "mcview.h"
#include "DiaInputD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiaInputD dialog
CDiaInputD::CDiaInputD(CWnd* pParent /*=NULL*/)
	: CDialog(CDiaInputD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiaInputD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bVisible=false;
}


void CDiaInputD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiaInputD)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiaInputD, CDialog)
	//{{AFX_MSG_MAP(CDiaInputD)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiaInputD message handlers

void CDiaInputD::RefreshShow()
{
	SetWindowText((LPCTSTR)(m_pInputD->m_WndPrm));
	SetDlgItemText(IDC_SET,(LPCTSTR)(m_pInputD->m_SetPrm));
	SetDlgItemText(IDC_RESET,(LPCTSTR)(m_pInputD->m_ResetPrm));
	CWnd *pWnd;
	if(m_pInputD->m_TagValue.Flags & TF_Valid){
		pWnd=GetDlgItem(IDC_SET);
		pWnd->EnableWindow();
		pWnd=GetDlgItem(IDC_RESET);
		pWnd->EnableWindow();
		if(m_pInputD->m_TagValue.Value.iValue){
			SetDlgItemText(IDC_STATUS,(LPCTSTR)(m_pInputD->m_OnMsg));
		}else{
			SetDlgItemText(IDC_STATUS,(LPCTSTR)(m_pInputD->m_OffMsg));
		}
	}else{
		pWnd=GetDlgItem(IDC_SET);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_RESET);
		pWnd->EnableWindow(FALSE);
		SetDlgItemText(IDC_STATUS,"N/A");
	}
}

void CDiaInputD::OnSet() 
{
	TAG_NAME tn;
	tagname_by_text(&tn,(LPCTSTR)m_pInputD->m_TagName);

    TAG_VALUE tv;
	tv.iValue=1;

    proxy_write_tags(1, &tn, &tv);	
}

void CDiaInputD::OnReset() 
{
	TAG_NAME tn;
	tagname_by_text(&tn,(LPCTSTR)m_pInputD->m_TagName);

    pmc_value_t tg;
	tg.Flags |= TF_Valid;
	tg.Value.iValue=0;

    proxy_write_tags(1, &tn, &tg.Value);
}
