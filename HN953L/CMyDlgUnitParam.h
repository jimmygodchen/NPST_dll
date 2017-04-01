#if !defined(AFX_CMYDLGUNITPARAM_H__684A9D34_B79D_416F_90BC_8E6D753CA875__INCLUDED_)
#define AFX_CMYDLGUNITPARAM_H__684A9D34_B79D_416F_90BC_8E6D753CA875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgUnitParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDlgUnitParam dialog

class CMyDlgUnitParam : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CMyDlgUnitParam)

// Construction
public:
	CMyDlgUnitParam();
	~CMyDlgUnitParam();

// Dialog Data
	//{{AFX_DATA(CMyDlgUnitParam)
	enum { IDD = IDD_UNIT_PARAM };
	int		m_nAddr;
	int		m_nTimeout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgUnitParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyDlgUnitParam)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGUNITPARAM_H__684A9D34_B79D_416F_90BC_8E6D753CA875__INCLUDED_)
