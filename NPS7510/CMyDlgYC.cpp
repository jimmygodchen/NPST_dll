// CMyDlgYC.cpp : implementation file
//

#include "stdafx.h"
#include "NPS7510.h"
#include "CMyDlgYC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgYC dialog


CMyDlgYC::CMyDlgYC(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlgYC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgYC)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyDlgYC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgYC)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgYC, CDialog)
	//{{AFX_MSG_MAP(CMyDlgYC)
	ON_BN_CLICKED(IDC_BTN_H, OnBtnH)
	ON_BN_CLICKED(IDC_BTN_F, OnBtnF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgYC message handlers

BOOL CMyDlgYC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pDataYC);
    CString strTile = _T("Ò£¿Ø-<") + m_pDataYC->m_strName + _T(">");
    SetWindowText(strTile);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlgYC::OnBtnH() 
{
	// TODO: Add your control notification handler code here
	m_pDataYC->SetOperateCode(0x55);
}

void CMyDlgYC::OnBtnF() 
{
	// TODO: Add your control notification handler code here
    m_pDataYC->SetOperateCode(0x33);
}

void CMyDlgYC::OnOK() 
{
	// TODO: Add extra validation here
    m_pDataYC->SetOperateCode(0xaa);
	
// 	CDialog::OnOK();
}
