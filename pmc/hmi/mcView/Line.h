// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__CB0CA93D_7CED_4F16_8752_1818C8515596__INCLUDED_)
#define AFX_LINE_H__CB0CA93D_7CED_4F16_8752_1818C8515596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"

class CLine : public CElement  
{
	DECLARE_DYNAMIC(CLine)
public:
	virtual void UpdateView();
	virtual void MoveElement(POINT potOffset);
	virtual void MoveInCell(POINT potTracker);
	void Load(IXMLDOMElementPtr pGO);
	virtual void Save(IXMLDOMElementPtr pRoot);
	virtual CElement * Clone(long lCmdId,long lStatus);
	virtual void Format(long left,long top,long right,long bottom,long flag);
	virtual long Bottom();
	virtual long Top();
	virtual long Right();
	virtual long Left();
	virtual bool RInR(LPCRECT lpRect);
	virtual long HitTest(long x,long y);
	virtual void DrawHotPoints(CDC *pDC);
	virtual void DrawTracker(CDC *pDC);
	virtual void Draw(CDC *pDC);
	LOGPEN m_pen;
	LOGPEN m_open;
	long m_ly2;
	long m_lx2;
	long m_ly1;
	long m_lx1;
	long m_loy2;
	long m_lox2;
	long m_loy1;
	long m_lox1;
	CLine();
	virtual ~CLine();

};

#endif // !defined(AFX_LINE_H__CB0CA93D_7CED_4F16_8752_1818C8515596__INCLUDED_)
