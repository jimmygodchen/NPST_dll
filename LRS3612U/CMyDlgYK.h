#if !defined(AFX_CMYDLGYK_H__E4173B07_D130_48B2_AB1D_45D4C36E6B48__INCLUDED_)
#define AFX_CMYDLGYK_H__E4173B07_D130_48B2_AB1D_45D4C36E6B48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgYK.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDlgYK dialog

class CMyDlgYK : public CDialog
{
// Construction
public:
	CMyDlgYK(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgYK)
	enum { IDD = IDD_DLG_YK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
    CMyDeviceYK* m_pYK;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgYK)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgYK)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnH();
	afx_msg void OnBtnF();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGYK_H__E4173B07_D130_48B2_AB1D_45D4C36E6B48__INCLUDED_)
