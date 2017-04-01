#if !defined(AFX_CMYDLGOPLIST_H__CDB57213_7E9F_469C_9C5D_0BB5DDC8377C__INCLUDED_)
#define AFX_CMYDLGOPLIST_H__CDB57213_7E9F_469C_9C5D_0BB5DDC8377C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgOpList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDlgOpList dialog

class CMyDlgOpList : public CBCGPDialog
{
// Construction
public:
	CMyDlgOpList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgOpList)
	enum { IDD = IDD_DLG_OPLIST };
	CStatic	m_wndLocation;
	//}}AFX_DATA

public:
    CBCGPGridCtrl m_wndGrid;
    CMyDataHN953OPList* m_pOPList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgOpList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgOpList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGOPLIST_H__CDB57213_7E9F_469C_9C5D_0BB5DDC8377C__INCLUDED_)
