// CMyDlgUnitParam.cpp : implementation file
//

#include "stdafx.h"
#include "CMyDlgUnitParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgUnitParam property page

IMPLEMENT_DYNCREATE(CMyDlgUnitParam, CBCGPPropertyPage)

CMyDlgUnitParam::CMyDlgUnitParam() : CBCGPPropertyPage(CMyDlgUnitParam::IDD)
{
	//{{AFX_DATA_INIT(CMyDlgUnitParam)
	m_nAddr = 0;
	m_nTimeout = 0;
	//}}AFX_DATA_INIT
}

CMyDlgUnitParam::~CMyDlgUnitParam()
{
}

void CMyDlgUnitParam::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgUnitParam)
	DDX_Text(pDX, IDC_EDIT_ADDR, m_nAddr);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_nTimeout);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgUnitParam, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CMyDlgUnitParam)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgUnitParam message handlers
