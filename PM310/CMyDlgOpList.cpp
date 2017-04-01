// CMyDlgOpList.cpp : implementation file
//

#include "stdafx.h"
#include "CMyUnitModbus.h"
#include "PM310.h"
#include "CMyGridCtrl.h"
#include "CMyDlgOpList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgOpList dialog


CMyDlgOpList::CMyDlgOpList(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgOpList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgOpList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pOPList = NULL;
    EnableLayout();
}


void CMyDlgOpList::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgOpList)
	DDX_Control(pDX, IDC_LIST_PARAM, m_wndLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgOpList, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgOpList)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgOpList message handlers

static CMyDataPMOPList* s_pOPList = NULL;

static BOOL CALLBACK GridCallback (BCGPGRID_DISPINFO* pdi, LPARAM)
{
    ASSERT (pdi != NULL);
    
    int nRow = pdi->item.nRow;	// Row of an item
    int nCol = pdi->item.nCol;	// Column of an item
    
    if(nCol == 0)
    {
        pdi->item.varValue = (long) (nRow+1);
    }
    else if(nCol==1)
    {
        pdi->item.varValue = (LPCTSTR)s_pOPList->m_arOPList[nRow].strName;
    }
//     else
//     {
//         pdi->item.varValue = (long)(s_pOPList->m_arOPList[nRow].nIndex);
//     }
    
    return TRUE;
}

BOOL CMyDlgOpList::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CWaitCursor wait;
    
    CRect rectGrid;
    m_wndLocation.GetClientRect (&rectGrid);
    m_wndLocation.MapWindowPoints (this, &rectGrid);
    
    m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
    m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
    m_wndGrid.EnableInvertSelOnCtrl ();
    
    // Set grid tab order (first):
    m_wndGrid.SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    
    m_wndGrid.SetReadOnly ();
    
    m_wndGrid.InsertColumn (0, _T("序号"), 35);
    m_wndGrid.InsertColumn (1, _T("名称"), 200);
//     m_wndGrid.InsertColumn (2, _T("数据编号"), 80);
    
    ASSERT(m_pOPList);
    s_pOPList = m_pOPList;
    
    int nSize = m_pOPList->m_arOPList.GetSize();
    m_wndGrid.EnableVirtualMode (GridCallback);
    m_wndGrid.SetVirtualRows (nSize);
    m_wndGrid.AdjustLayout ();
    
    // Set grid colors
    CBCGPGridColors colors;
    colors.m_LeftOffsetColors.m_clrBackground = globalData.clrWindow;
    m_wndGrid.SetColorTheme (colors);
    
    CBCGPGridColors theme;
    CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme(&m_wndGrid, theme);
    //     m_wndGridFloat.SendMessage(BCGM_ONSETCONTROLVMMODE, TRUE);
    m_wndGrid.SetColorTheme(theme);
    
    CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
    if(pLayout != NULL)
    {
        pLayout->AddAnchor(IDC_LIST_PARAM, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
        pLayout->AddAnchor(IDOK, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
        pLayout->AddAnchor(IDCANCEL, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlgOpList::OnOK() 
{
	// TODO: Add extra validation here
    int nIndex = -1;
    int nSize = m_pOPList->m_arOPList.GetSize();
    for(int i=0;i<nSize;++i)
    {
        if(m_wndGrid.IsRowSelected(i))
        {
            nIndex = i;
        }
    }
    
    if(nIndex>nSize-1 || nIndex<0)
    {
        MessageBox("请选择要读取的数据!");
        return;
    }
    m_pOPList->SndCmd(nIndex);
}

void CMyDlgOpList::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
    int nSize = m_pOPList->m_arOPList.GetSize();
    //     m_wndGrid.EnableVirtualMode (GridCallback);
    m_wndGrid.SetVirtualRows (nSize);
    m_wndGrid.AdjustLayout ();
}
