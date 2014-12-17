#if !defined(AFX_DIASYSTEM_H__0DBC715E_81BC_4BB9_B924_6E650AFD4C51__INCLUDED_)
#define AFX_DIASYSTEM_H__0DBC715E_81BC_4BB9_B924_6E650AFD4C51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiaSystem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiaSystem dialog

class CDiaSystem : public CDialog
{
// Construction
public:
	CString m_password[10];
	CDiaSystem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiaSystem)
	enum { IDD = IDD_SYSTEM };
	CListBox	m_sw2;
	int		m_rank;
	BOOL	m_noSwitch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiaSystem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiaSystem)
	virtual void OnCancel();
	afx_msg void OnRank0();
	afx_msg void OnRank1();
	afx_msg void OnRank2();
	afx_msg void OnRank3();
	afx_msg void OnRank4();
	afx_msg void OnRank5();
	afx_msg void OnRank6();
	afx_msg void OnRank7();
	afx_msg void OnRank8();
	afx_msg void OnRank9();
	virtual BOOL OnInitDialog();
	afx_msg void OnReturnWnd();
	afx_msg void OnChgPwd();
	afx_msg void OnPrint();
	afx_msg void OnAbout();
	afx_msg void OnNoswitch();
	afx_msg void OnDblclkSw2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SavePassword();
	void LoadPassword();
	void SetButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIASYSTEM_H__0DBC715E_81BC_4BB9_B924_6E650AFD4C51__INCLUDED_)
