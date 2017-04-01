#if !defined(AFX_CMYDLGREGULATE_H__6BCF3641_1305_4B93_A0D4_B450A54CD7CD__INCLUDED_)
#define AFX_CMYDLGREGULATE_H__6BCF3641_1305_4B93_A0D4_B450A54CD7CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgRegulate.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMyRegulateGridCtrl sample class

class CMyRegulateGridCtrl: public CBCGPGridCtrl
{
public:
    CMyRegulateGridCtrl();
    ~CMyRegulateGridCtrl();
    
public:
    void Mem2Ctr(void);
    void Ctr2Mem(void);

protected:
    CBCGPGridRow* CreateNewRow(void);
    void AddRowEdit(CString strLable, short nR, short nX);
    REGULATE GetRowEdit(int nPos);

public:
    REGULATESET m_RegulateR;
    REGULATESET m_RegulateW;
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CMyRegulateGridCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CMyDlgRegulate dialog

class CMyDlgRegulate : public CBCGPDialog// CDialog
{
// Construction
public:
	CMyDlgRegulate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgRegulate)
	enum { IDD = IDD_DLG_REGULATE };
	CStatic	m_wndLocation;
	//}}AFX_DATA

public:
    CMyRegulateGridCtrl m_wndGrid;
    CMyDataNPSRegulate* m_pDataRegulte;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgRegulate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgRegulate)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGREGULATE_H__6BCF3641_1305_4B93_A0D4_B450A54CD7CD__INCLUDED_)
