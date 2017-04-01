#if !defined(AFX_CMYDLGSETPOINT_H__75403053_A4EC_41F9_8A1A_2ABFFEDE9DEB__INCLUDED_)
#define AFX_CMYDLGSETPOINT_H__75403053_A4EC_41F9_8A1A_2ABFFEDE9DEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgSetpoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySetpointGridCtrl sample class

class CMySetpointGridCtrl: public CMyGridCtrl
{
public:
    CMySetpointGridCtrl();
    ~CMySetpointGridCtrl();
    
public:
    void Mem2Ctr(void);
    void Ctr2Mem(void);
    
public:
    tDEVICESETPOINT m_SetpointR;
    tDEVICESETPOINT m_SetpointW;
    tDEVICESETPOINT_PM* m_pSetpointR;
    tDEVICESETPOINT_PM* m_pSetpointW;
    
public:
    CBCGPGridRow* AddProtectTog(CString strLable, WORD wTog);
    void AddEditSub(CBCGPGridRow* pRoot, CString strLable, float fValue, CString strUnit);
    void AddTogSub(CBCGPGridRow* pRoot, CString strLable, WORD wTog);
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CMySetpointGridCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CMyDlgSetpoint dialog

class CMyDlgSetpoint : public CBCGPDialog
{
// Construction
public:
	CMyDlgSetpoint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgSetpoint)
	enum { IDD = IDD_DLG_SETPOINT };
	CStatic	m_wndLocation;
	//}}AFX_DATA

public:
    CMySetpointGridCtrl m_wndGrid;
    CMyDataPMSetpoint* m_pDataSetpoint;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgSetpoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgSetpoint)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGSETPOINT_H__75403053_A4EC_41F9_8A1A_2ABFFEDE9DEB__INCLUDED_)
