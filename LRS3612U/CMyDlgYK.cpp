// CMyDlgYK.cpp : implementation file
//

#include "stdafx.h"
#include "CMyUnitModbus.h"
#include "CMyUnitDevice.h"
#include "CMyDlgYK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgYK dialog


CMyDlgYK::CMyDlgYK(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlgYK::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgYK)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyDlgYK::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgYK)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgYK, CDialog)
	//{{AFX_MSG_MAP(CMyDlgYK)
	ON_BN_CLICKED(IDC_BTN_H, OnBtnH)
	ON_BN_CLICKED(IDC_BTN_F, OnBtnF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgYK message handlers

BOOL CMyDlgYK::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pYK);
    CString strTile = _T("Ò£¿Ø-<") + m_pYK->m_strName + _T(">");
    SetWindowText(strTile);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlgYK::OnBtnH() 
{
	// TODO: Add your control notification handler code here
	m_pYK->SetOperateCode(0x55);
}

void CMyDlgYK::OnBtnF() 
{
	// TODO: Add your control notification handler code here
	m_pYK->SetOperateCode(0x33);
}

void CMyDlgYK::OnOK() 
{
	// TODO: Add extra validation here
    m_pYK->SetOperateCode(0xaa);
// 	CDialog::OnOK();
}
