#if !defined(AFX_CMYDLGPARAM_H__4106512E_0CC9_4620_90CD_F3D72A277A16__INCLUDED_)
#define AFX_CMYDLGPARAM_H__4106512E_0CC9_4620_90CD_F3D72A277A16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgParam.h : header file
//

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
    tDEVICEPARAM m_ParamR;
    tDEVICEPARAM m_ParamW;
    tDEVICEPARAM_PM* m_pParamPMR;
    tDEVICEPARAM_PM* m_pParamPMW;
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CMyParamGridCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMyDlgParam dialog

class CMyDlgParam : public CBCGPDialog  // CDialog
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
    CMyDataPMParam* m_pDataParam;

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
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGPARAM_H__4106512E_0CC9_4620_90CD_F3D72A277A16__INCLUDED_)
