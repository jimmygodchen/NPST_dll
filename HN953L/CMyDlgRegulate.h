#if !defined(AFX_CMYDLGREGULATE_H__5B70A660_B148_42DA_A1A3_2A04CC10A537__INCLUDED_)
#define AFX_CMYDLGREGULATE_H__5B70A660_B148_42DA_A1A3_2A04CC10A537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgRegulate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyRegulateGridCtrl sample class

class CMyRegulateGridCtrl: public CBCGPGridCtrl
{
public:
    CMyRegulateGridCtrl();
    ~CMyRegulateGridCtrl();
    
public:
    void AddCtrl(void);
    void Ctrl2Mem(void);
    
protected:
    CBCGPGridRow* CreateNewRow(void);
    void AddRowEdit(CString strLable, short nR, short nX);
    tREGULATE GetRowEdit(int nPos);
    
public:
    tREGULATE m_Regulate[DFT_CHANNEL_HARD];
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CMyRegulateGridCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMyDlgRegulate dialog

class CMyDlgRegulate : public CBCGPDialog
{
// Construction
public:
	CMyDlgRegulate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgRegulate)
	enum { IDD = IDD_DLG_REGUALTE };
	CStatic	m_wndLocation;
	//}}AFX_DATA

public:
    CMyRegulateGridCtrl m_wndGrid;
    CMyDataMem* m_pRegulate;

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
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGREGULATE_H__5B70A660_B148_42DA_A1A3_2A04CC10A537__INCLUDED_)
