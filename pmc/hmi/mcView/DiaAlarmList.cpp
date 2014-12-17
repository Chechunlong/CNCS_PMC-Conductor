// DiaAlarmList.cpp : implementation file
//

#include "stdafx.h"
#include "mcview.h"
#include "DiaAlarmList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiaAlarmList dialog

CDiaAlarmList::CDiaAlarmList(CWnd* pParent /*=NULL*/)
	: CDialog(CDiaAlarmList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiaAlarmList)
	m_ShowOperations = FALSE;
	//}}AFX_DATA_INIT
}

CDiaAlarmList::~CDiaAlarmList()
{
}


void CDiaAlarmList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiaAlarmList)
	DDX_Control(pDX, IDC_ALARMLIST, m_list);
	DDX_Check(pDX, IDC_CHECK1, m_ShowOperations);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiaAlarmList, CDialog)
//{{AFX_MSG_MAP(CDiaAlarmList)
ON_BN_CLICKED(IDC_ACK, OnAck)
ON_BN_CLICKED(IDC_ACKALL, OnAckall)
ON_NOTIFY(LVN_GETDISPINFO, IDC_ALARMLIST, OnGetdispinfoAlarmlist)
ON_BN_CLICKED(IDC_CHECK1, OnShowOperations)
//}}AFX_MSG_MAP
ON_NOTIFY(NM_CUSTOMDRAW, IDC_ALARMLIST, OnAlarmDrawList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiaAlarmList message handlers

void CDiaAlarmList::UpdateList()
{
	LV_ITEM listItem;
	int pt, guardian;
	int topItem;

	ZeroMemory(&listItem, sizeof(listItem));
	listItem.mask = LVIF_TEXT|LVIF_PARAM;

	m_list.SetRedraw(FALSE);
	m_list.DeleteAllItems();
	if(g_AlarmQueueTail < 0){
		goto __done;
	}
	
	guardian = g_AlarmQueueTail;
	pt = (g_AlarmQueueTail + 1) % RCT_ALARM_COUNT;
	for(;;){
		CAlarmRecord * r;
		r = &g_AlarmRecords[pt];
		if(r->m_valid){
			listItem.iSubItem = 0;
			listItem.iItem = m_list.GetItemCount();
			listItem.pszText = LPSTR_TEXTCALLBACK;
			listItem.cchTextMax = 50;
			listItem.lParam = (LPARAM)pt;
			
			m_list.InsertItem(&listItem);
			m_list.SetItemText(listItem.iItem, 1, LPSTR_TEXTCALLBACK);
		}
		if(pt == guardian){
			break;
		}
		pt++;
		if(pt == RCT_ALARM_COUNT){
			pt = 0;
		}
	}
#if 1
	topItem = g_TopAlarmPt;
	if(topItem >= 0){
		m_list.SetSelectionMark(topItem);
		m_list.SetItem(
			topItem, 
			0, 
			LVIF_STATE, 
			0, 
			0, 
			LVIS_SELECTED, 
			LVIS_SELECTED,
			0
			);
		m_list.EnsureVisible(topItem, FALSE);
	}
#endif
__done:
	m_list.SetRedraw(TRUE);
}

BOOL CDiaAlarmList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LV_COLUMN listColumn;
	TCHAR* rgszColumns[] = { _T("ÐòºÅ"), _T("ÊÂ¼þ")};
	listColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	listColumn.fmt = LVCFMT_LEFT;
	listColumn.cx = 40;
	listColumn.iSubItem = 0;
	listColumn.pszText = rgszColumns[0];
	m_list.InsertColumn(0, &listColumn);
	listColumn.iSubItem = 1;
	listColumn.pszText = rgszColumns[1];
	listColumn.cx = 480;
	m_list.InsertColumn(1, &listColumn);

#if 0
	ListView_SetExtendedListViewStyle(
		m_list.m_hWnd,
		ListView_GetExtendedListViewStyle(m_list.m_hWnd) 
		| LVS_EX_FULLROWSELECT
	);
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDiaAlarmList::OnAck() 
{
	long selected = m_list.GetSelectionMark();
	if(selected < 0) {
		return;
	}
	long pt;
	pt = m_list.GetItemData(selected);
	if(pt < 0){
		return;
	}
	CAlarmRecord *pAlarm = g_AlarmRecords + pt;
	pAlarm->m_ack=true;
	int i, topItem, topRank;
	topItem = -1;
	topRank = -1;
	for(i=selected - 1; i >= 0; i--){
		pt = m_list.GetItemData(i);
		assert(pt >= 0);
		if(!g_AlarmRecords[pt].m_ack && g_AlarmRecords[pt].m_rank > topRank){
			topRank = g_AlarmRecords[pt].m_rank;
			topItem = i;
		}
	}
	if(topItem >= 0){
		m_list.SetSelectionMark(topItem);
		m_list.SetItem(
			topItem, 
			0, 
			LVIF_STATE, 
			0, 
			0, 
			LVIS_SELECTED, 
			LVIS_SELECTED,
			0
			);
		m_list.EnsureVisible(topItem, FALSE);
	}
	m_list.RedrawWindow();
}

void CDiaAlarmList::OnAckall()
{
	CAlarmRecord *pAlarm;
	pAlarm = g_AlarmRecords;
	for(int i=0;i<RCT_ALARM_COUNT;i++, pAlarm++){
		pAlarm->m_ack=true;
	}
	g_TopAlarmPt = -1;
	m_list.RedrawWindow();
}

void CDiaAlarmList::OnAlarmDrawList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLVCUSTOMDRAW pDraw = (LPNMLVCUSTOMDRAW)pNMHDR;
	
	// Determine the drawing stage.
	DWORD dwDrawStage = pDraw->nmcd.dwDrawStage;
	*pResult = CDRF_NOTIFYITEMDRAW|CDRF_NOTIFYPOSTPAINT|CDRF_NOTIFYPOSTERASE;
	
	if(dwDrawStage & CDDS_ITEM)
	{
		long pt=pDraw->nmcd.lItemlParam;
		
		CAlarmRecord * pAlarm = g_AlarmRecords + pt;
		if(pAlarm->m_ack){
			pDraw->clrText = RGB(128,128,128);
		}else{
			if(pAlarm->m_ac==AC_Alarm){
				pDraw->clrText = RGB(255,0,0);
			}else if(pAlarm->m_ac==AC_CancelAlarm){
				pDraw->clrText = RGB(0,192,0);
			}else if(pAlarm->m_ac==AC_AckAlarm){
				pDraw->clrText = RGB(128,128,128);
			}else if(pAlarm->m_ac==AC_WriteDevice){
				pDraw->clrText = RGB(0,0,192);
			}else{
				pDraw->clrText = RGB(0,0,0);
			}
			if(pt == g_TopAlarmPt) {
				pDraw->clrTextBk=RGB(192,192,255);
			}
		}
	}
}

void CDiaAlarmList::OnGetdispinfoAlarmlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;	
	long pt=pDispInfo->item.lParam;
	bool bSel;
	LVITEM * it;
	it = &pDispInfo->item;

	if(it->state & LVIS_SELECTED){
		bSel = true;
	}else{
		bSel = false;
	}
	
	char pc[6];
	if(bSel){
		sprintf(pc,"->%3d", it->iItem);
	}else{
		sprintf(pc,"%5d", it->iItem);
	}
	
	CAlarmRecord * pAlarm = g_AlarmRecords + pt;
	
	if(it->mask & LVIF_TEXT){
		LPTSTR& pszText = pDispInfo->item.pszText;
		switch(pDispInfo->item.iSubItem){
		case 0:
			pszText = pc;
			break;
		case 1:
			pszText = pAlarm->m_msg;
			break;
		default:
			ASSERT(0);
		}
	}
	
	*pResult = 0;
}

void CDiaAlarmList::OnShowOperations() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_bShowAllAlarms = m_ShowOperations? true : false;
	UpdateList();	
}

