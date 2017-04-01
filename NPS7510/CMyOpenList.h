#if !defined(AFX_CMYOPENLIST_H__8EF047DB_38DB_4714_834E_C195E9CF36D3__INCLUDED_)
#define AFX_CMYOPENLIST_H__8EF047DB_38DB_4714_834E_C195E9CF36D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyOpenList.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMyOpenList dialog

class CMyOpenList : public CBCGPDialog//CDialog
{
// Construction
public:
	CMyOpenList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyOpenList)
	enum { IDD = IDD_DLG_OPLIST };
	CStatic	m_wndLocation;
	//}}AFX_DATA

public:
    CBCGPGridCtrl m_wndGrid;
    CMyDataOPList* m_pOPList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyOpenList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyOpenList)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYOPENLIST_H__8EF047DB_38DB_4714_834E_C195E9CF36D3__INCLUDED_)
