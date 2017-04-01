// CMyNPS7510Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMyNPS7510Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyNPS7510Dlg property page

IMPLEMENT_DYNCREATE(CMyNPS7510Dlg, CBCGPPropertyPage)

CMyNPS7510Dlg::CMyNPS7510Dlg() : CBCGPPropertyPage(CMyNPS7510Dlg::IDD)
{
	//{{AFX_DATA_INIT(CMyNPS7510Dlg)
	m_nAddr = 0;
	m_nTimeout = 0;
	//}}AFX_DATA_INIT
}

CMyNPS7510Dlg::~CMyNPS7510Dlg()
{
}

void CMyNPS7510Dlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyNPS7510Dlg)
	DDX_Text(pDX, IDC_EDIT_ADDR, m_nAddr);
	DDV_MinMaxInt(pDX, m_nAddr, 1, 255);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_nTimeout);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyNPS7510Dlg, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CMyNPS7510Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyNPS7510Dlg message handlers
