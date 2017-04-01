#if !defined(AFX_CMYDLGYC_H__F690CCD8_9A8B_4B21_95E4_B62D1F42ADDD__INCLUDED_)
#define AFX_CMYDLGYC_H__F690CCD8_9A8B_4B21_95E4_B62D1F42ADDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgYC.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMyDlgYC dialog

class CMyDlgYC : public CDialog
{
// Construction
public:
	CMyDlgYC(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgYC)
	enum { IDD = IDD_DLG_YC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
    CMyDataNPSYC* m_pDataYC;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgYC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgYC)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnH();
	afx_msg void OnBtnF();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGYC_H__F690CCD8_9A8B_4B21_95E4_B62D1F42ADDD__INCLUDED_)
