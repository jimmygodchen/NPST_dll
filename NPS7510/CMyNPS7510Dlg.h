#if !defined(AFX_CMYNPS7510DLG_H__4A44F91F_EBFF_470F_9769_847D2F7307A4__INCLUDED_)
#define AFX_CMYNPS7510DLG_H__4A44F91F_EBFF_470F_9769_847D2F7307A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyNPS7510Dlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMyNPS7510Dlg dialog

class CMyNPS7510Dlg : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CMyNPS7510Dlg)

// Construction
public:
	CMyNPS7510Dlg();
	~CMyNPS7510Dlg();

// Dialog Data
	//{{AFX_DATA(CMyNPS7510Dlg)
	enum { IDD = IDD_UNIT_NPS7510 };
	int		m_nAddr;
	int		m_nTimeout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyNPS7510Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyNPS7510Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYNPS7510DLG_H__4A44F91F_EBFF_470F_9769_847D2F7307A4__INCLUDED_)
