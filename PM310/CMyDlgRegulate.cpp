// CMyDlgRegulate.cpp : implementation file
//

#include "stdafx.h"
#include "CMyUnitModbus.h"
#include "PM310.h"
#include "CMyGridCtrl.h"
#include "CMyDlgRegulate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMyRegulateGridCtrl sample class
CMyRegulateGridCtrl::CMyRegulateGridCtrl()
{
}

CMyRegulateGridCtrl::~CMyRegulateGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyRegulateGridCtrl, CBCGPGridCtrl)
    //{{AFX_MSG_MAP(CMyRegulateGridCtrl)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRegulateGridCtrl message handlers

int CMyRegulateGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    EnableColumnAutoSize (TRUE);
    SetSingleSel (FALSE);
    EnableGroupByBox (FALSE);
    //     m_wndGridFloat.SetReadOnly ();
    SetWholeRowSel ();
    EnableHeader (TRUE, 0);
    
    // Set grid tab order (first):
    SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    
    InsertColumn (0, _T("名称"), 50);
    InsertColumn (1, _T("实部"), 50);
    InsertColumn (2, _T("虚部"), 50);

    Mem2Ctr();
    
    return 0;
}

CBCGPGridRow* CMyRegulateGridCtrl::CreateNewRow(void)
{
    int nColumnCount = GetColumnCount();
    CBCGPGridRow* pRow = CreateRow(nColumnCount);
    ASSERT(pRow);

    pRow->GetItem(0)->AllowEdit(FALSE);
    pRow->GetItem(1)->AllowEdit(TRUE);
    pRow->GetItem(2)->AllowEdit(TRUE);

    return pRow;
}

void CMyRegulateGridCtrl::AddRowEdit(CString strLable, short nR, short nX)
{
    _variant_t var;

    CBCGPGridRow* pRow = CreateNewRow();
    ASSERT(pRow);
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);
    float fR = nR*0.0001f;
    float fX = nX*0.0001f;
    var = (_variant_t)fR;
    pRow->GetItem(1)->SetValue(var);
    var = (_variant_t)fX;
    pRow->GetItem(2)->SetValue(var);
    AddRow(pRow, FALSE);
}

REGULATE CMyRegulateGridCtrl::GetRowEdit(int nPos)
{
    REGULATE reg;
    _variant_t var;
    CBCGPGridRow* pRow = GetRow(nPos);
    ASSERT(pRow);
    var = pRow->GetItem(1)->GetValue();
    if(var.vt==VT_R4)
    {
         reg.nRegulateR = bcg_round((float)var*10000);
    }
    var = pRow->GetItem(2)->GetValue();
    if(var.vt==VT_R4)
    {
        reg.nRegulateX = bcg_round((float)var*10000);
    }
    return reg;
}

void CMyRegulateGridCtrl::Mem2Ctr(void)
{
    CBCGPGridRow::m_strFormatFloat = _T("%.4f");
    AddRowEdit(_T("Ia"), m_RegulateR.regulate[0].nRegulateR, m_RegulateR.regulate[0].nRegulateX);
    AddRowEdit(_T("Ib"), m_RegulateR.regulate[1].nRegulateR, m_RegulateR.regulate[1].nRegulateX);
    AddRowEdit(_T("Ic"), m_RegulateR.regulate[2].nRegulateR, m_RegulateR.regulate[2].nRegulateX);
    AddRowEdit(_T("Ua"), m_RegulateR.regulate[3].nRegulateR, m_RegulateR.regulate[3].nRegulateX);
    AddRowEdit(_T("Ub"), m_RegulateR.regulate[4].nRegulateR, m_RegulateR.regulate[4].nRegulateX);
    AddRowEdit(_T("Uc"), m_RegulateR.regulate[5].nRegulateR, m_RegulateR.regulate[5].nRegulateX);
}

void CMyRegulateGridCtrl::Ctr2Mem(void)
{
    REGULATE reg;
    for(int nPos = 0; nPos<6; ++nPos)
    {
        reg = GetRowEdit(nPos);
        m_RegulateW.regulate[nPos] = reg;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CMyDlgRegulate dialog


CMyDlgRegulate::CMyDlgRegulate(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgRegulate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgRegulate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pDataRegulte = NULL;
    EnableLayout();
}


void CMyDlgRegulate::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgRegulate)
	DDX_Control(pDX, IDC_LIST_PARAM, m_wndLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgRegulate, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgRegulate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgRegulate message handlers

BOOL CMyDlgRegulate::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pDataRegulte);
    CWaitCursor wait;
    
    // Create grid tree:
    CRect rectGrid;
    m_wndLocation.GetClientRect (&rectGrid);
    m_wndLocation.MapWindowPoints (this, &rectGrid);
    
    m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, IDC_LIST_PARAM);
    
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

void CMyDlgRegulate::OnOK() 
{
	// TODO: Add extra validation here
// 	
// 	CBCGPDialog::OnOK();
    if(MyMessageBox("本操作将修改设备当前的运行参数,\t\n请确认是否下装?","请注意",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_wndGrid.Ctr2Mem();
        m_pDataRegulte->StoreToDevice(m_wndGrid.m_RegulateW);
    }
}
