#if !defined(AFX_CMYDLGPARAM_H__B8460960_1A3D_4A3D_91D9_9BFC17DB5542__INCLUDED_)
#define AFX_CMYDLGPARAM_H__B8460960_1A3D_4A3D_91D9_9BFC17DB5542__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgParam.h : header file
//

#include "resource.h"
#include "CMyGridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMyParamGridCtrl sample class

class CMyParamGridCtrl: public CMyGridCtrl
{
public:
    CMyParamGridCtrl();
    ~CMyParamGridCtrl();

public:
    void Mem2Ctr(void);
    void Ctr2Mem(void);

public:
    DEVICEPARAM m_ParamR;
    DEVICEPARAM m_ParamW;
    DEVICEPARAM_NPS* m_pParamNPSR;
    DEVICEPARAM_NPS* m_pParamNPSW;

    // Generated message map functions
protected:
    //{{AFX_MSG(CMyParamGridCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMyDlgParam dialog

class CMyDlgParam : public CBCGPDialog// CDialog
{
// Construction
public:
	CMyDlgParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgParam)
	enum { IDD = IDD_DLG_PARAM };
	CStatic	m_wndLocation;
	//}}AFX_DATA

public:
    CMyParamGridCtrl m_wndGrid;
    CMyDataNPSParam* m_pDataParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgParam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGPARAM_H__B8460960_1A3D_4A3D_91D9_9BFC17DB5542__INCLUDED_)
