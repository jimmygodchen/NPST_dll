// CMyDlgSetpoint.cpp : implementation file
//

#include "stdafx.h"
#include "CMyUnitModbus.h"
#include "PM310.h"
#include "CMyGridCtrl.h"
#include "CMyDlgSetpoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySetpointGridCtrl sample class

CMySetpointGridCtrl::CMySetpointGridCtrl()
{
}

CMySetpointGridCtrl::~CMySetpointGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMySetpointGridCtrl, CMyGridCtrl)
    //{{AFX_MSG_MAP(CMySetpointGridCtrl)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySetpointGridCtrl message handlers

int CMySetpointGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CMyGridCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_pSetpointR = (tDEVICESETPOINT_PM*)m_SetpointR.wSetpointArea1;
    m_pSetpointW = (tDEVICESETPOINT_PM*)m_SetpointW.wSetpointArea1;
    
    Mem2Ctr();
    
    return 0;
}

void CMySetpointGridCtrl::Mem2Ctr(void)
{
    float fData;

    CBCGPGridRow::m_strFormatFloat = _T("%.2f");

    int nIndex = 0;

    CBCGPGridRow* pRow = AddProtectTog(_T("电流I段"), m_SetpointR.wToggle[nIndex]);
    fData = m_pSetpointR->wDL1_SetI*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("A"));
    fData = m_pSetpointR->wDL1_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.wConfig[nIndex]);
    ++nIndex;

    pRow = AddProtectTog(_T("电流II段"), m_SetpointR.wToggle[nIndex]);
    fData = m_pSetpointR->wDL2_SetI*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("A"));
    fData = m_pSetpointR->wDL2_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.wConfig[nIndex]);
    ++nIndex;

    pRow = AddProtectTog(_T("过压I段"), m_SetpointR.wToggle[nIndex]);
    fData = m_pSetpointR->wGY1_SetU*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("V"));
    fData = m_pSetpointR->wDL2_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.wConfig[nIndex]);
    ++nIndex;

    pRow = AddProtectTog(_T("过压II段"), m_SetpointR.wToggle[nIndex]);
    fData = m_pSetpointR->wGY1_SetU*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("V"));
    fData = m_pSetpointR->wDL2_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.wConfig[nIndex]);
    ++nIndex;

    pRow = AddProtectTog(_T("欠压I段"), m_SetpointR.wToggle[nIndex]);
    fData = m_pSetpointR->wGY1_SetU*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("V"));
    fData = m_pSetpointR->wDL2_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.wConfig[nIndex]);
    ++nIndex;
    
    pRow = AddProtectTog(_T("欠压II段"), m_SetpointR.wToggle[nIndex]);
    fData = m_pSetpointR->wGY1_SetU*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("V"));
    fData = m_pSetpointR->wDL2_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.wConfig[nIndex]);

    nIndex = 0;
    pRow = AddProtectTog(_T("DI1"), m_SetpointR.INSetpoint[nIndex].wToggle);
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.INSetpoint[nIndex].wConfig);
    ++nIndex;

    pRow = AddProtectTog(_T("DI2"), m_SetpointR.INSetpoint[nIndex].wToggle);
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.INSetpoint[nIndex].wConfig);
    ++nIndex;

    pRow = AddProtectTog(_T("DI3"), m_SetpointR.INSetpoint[nIndex].wToggle);
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.INSetpoint[nIndex].wConfig);
    ++nIndex;

    pRow = AddProtectTog(_T("DI4"), m_SetpointR.INSetpoint[nIndex].wToggle);
    AddTogSub(pRow, _T("跳闸"), m_SetpointR.INSetpoint[nIndex].wConfig);
}

CBCGPGridRow* CMySetpointGridCtrl::AddProtectTog(CString strLable, WORD wTog)
{
    CBCGPGridRow* pRow = CreateNewRow();
    ASSERT_VALID(pRow);
    pRow->AllowSubItems();
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);

    CStringArray aContent;
    aContent.Add(_T("OFF"));
    aContent.Add(_T("ON"));
    int nSize = aContent.GetSize();
    CBCGPGridItem* pItem;
    if(wTog>=0 && wTog<nSize)
    {
        pItem = new CBCGPGridItem((LPCTSTR)aContent[wTog]);
    }
    else
    {
        pItem = new CBCGPGridItem((LPCTSTR)_T(""));
    }
    ASSERT(pItem);
    pItem->SetReadOnly(TRUE);
    for(int i=0;i<nSize;i++)
    {
        pItem->AddOption((LPCTSTR)aContent[i], TRUE);
    }
    pRow->ReplaceItem(1, pItem);
//     pRow->GetItem(2)->SetValue((LPCTSTR)strUnit);
    AddRow(pRow, FALSE);
    return pRow;
}

void CMySetpointGridCtrl::AddTogSub(CBCGPGridRow* pRoot, CString strLable, WORD wTog)
{
    ASSERT_VALID(pRoot);

    CBCGPGridRow* pRow = CreateNewRow();
    ASSERT_VALID(pRow);
    pRow->AllowSubItems();
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);
    
    CStringArray aContent;
    aContent.Add(_T("OFF"));
    aContent.Add(_T("ON"));
    int nSize = aContent.GetSize();
    CBCGPGridItem* pItem;
    if(wTog>=0 && wTog<nSize)
    {
        pItem = new CBCGPGridItem((LPCTSTR)aContent[wTog]);
    }
    else
    {
        pItem = new CBCGPGridItem((LPCTSTR)_T(""));
    }
    ASSERT(pItem);
    pItem->SetReadOnly(TRUE);
    for(int i=0;i<nSize;i++)
    {
        pItem->AddOption((LPCTSTR)aContent[i], TRUE);
    }
    pRow->ReplaceItem(1, pItem);
    pRoot->AddSubItem(pRow, FALSE);
}

void CMySetpointGridCtrl::AddEditSub(CBCGPGridRow* pRoot, CString strLable, float fValue, CString strUnit)
{
    ASSERT_VALID(pRoot);

    CBCGPGridRow* pSub = CreateNewRow();
    ASSERT_VALID(pSub);
    pSub->GetItem(0)->SetValue((LPCTSTR)strLable);
    _variant_t var;
    var = (_variant_t)fValue;
    pSub->GetItem(1)->SetValue(var);
    pSub->GetItem(2)->SetValue((LPCTSTR)strUnit);
    pRoot->AddSubItem(pSub, FALSE);
}

void CMySetpointGridCtrl::Ctr2Mem(void)
{
    int nPos = 0, nIndex = 0;
    float fData;

    m_SetpointW.wToggle[nIndex] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL1_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL1_SetT = fData*100;
    m_SetpointW.wConfig[nIndex] = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.wToggle[nIndex] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL2_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL2_SetT = fData*100;
    m_SetpointW.wConfig[nIndex] = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.wToggle[nIndex] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGY1_SetU = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGY1_SetT = fData*100;
    m_SetpointW.wConfig[nIndex] = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.wToggle[nIndex] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGY2_SetU = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGY2_SetT = fData*100;
    m_SetpointW.wConfig[nIndex] = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.wToggle[nIndex] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wQY1_SetU = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wQY1_SetT = fData*100;
    m_SetpointW.wConfig[nIndex] = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.wToggle[nIndex] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGY2_SetU = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGY2_SetT = fData*100;
    m_SetpointW.wConfig[nIndex] = GetRowCombox(nPos++);

    nIndex = 0;
    m_SetpointW.INSetpoint[nIndex].wToggle = GetRowCombox(nPos++);
    m_SetpointW.INSetpoint[nIndex].wConfig = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.INSetpoint[nIndex].wToggle = GetRowCombox(nPos++);
    m_SetpointW.INSetpoint[nIndex].wConfig = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.INSetpoint[nIndex].wToggle = GetRowCombox(nPos++);
    m_SetpointW.INSetpoint[nIndex].wConfig = GetRowCombox(nPos++);
    ++nIndex;

    m_SetpointW.INSetpoint[nIndex].wToggle = GetRowCombox(nPos++);
    m_SetpointW.INSetpoint[nIndex].wConfig = GetRowCombox(nPos++);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDlgSetpoint dialog


CMyDlgSetpoint::CMyDlgSetpoint(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgSetpoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgSetpoint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pDataSetpoint = NULL;
    EnableLayout();
}


void CMyDlgSetpoint::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgSetpoint)
	DDX_Control(pDX, IDC_LIST_PARAM, m_wndLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgSetpoint, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgSetpoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgSetpoint message handlers

BOOL CMyDlgSetpoint::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
    // TODO: Add extra initialization here
    ASSERT(m_pDataSetpoint);
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

void CMyDlgSetpoint::OnOK() 
{
	// TODO: Add extra validation here
// 	
// 	CBCGPDialog::OnOK();
    if(MyMessageBox("本操作将修改设备当前的运行参数,\t\n请确认是否下装?","请注意",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_wndGrid.Ctr2Mem();
        m_pDataSetpoint->StoreToDevice(m_wndGrid.m_SetpointW);
    }
}
