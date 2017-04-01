// CMyDlgSetpoint.cpp : implementation file
//

#include "stdafx.h"
#include "CMyUnitModbus.h"
#include "CMyUnitHN953L.h"
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

    m_pSetpoint = (tDEVICESETPOINTNPS*)m_Setpoint.wSetpointArea1;
    
    AddCtrl();
    
    return 0;
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

void CMySetpointGridCtrl::AddEditSub(CBCGPGridRow* pRoot, CString strLable, short nValue, CString strUnit)
{
    ASSERT_VALID(pRoot);
    
    CBCGPGridRow* pSub = CreateNewRow();
    ASSERT_VALID(pSub);
    pSub->GetItem(0)->SetValue((LPCTSTR)strLable);
    _variant_t var;
    var = (_variant_t)nValue;
    pSub->GetItem(1)->SetValue(var);
    pSub->GetItem(2)->SetValue((LPCTSTR)strUnit);
    pRoot->AddSubItem(pSub, FALSE);
}

void CMySetpointGridCtrl::AddCtrl(void)
{
    int nProIndex = 0;
    float fData;
    CBCGPGridRow::m_strFormatFloat = _T("%.2f");

    CBCGPGridRow* pRow = AddProtectTog(_T("备自投"), m_Setpoint.wToggle[nProIndex++]);
    AddEditSub(pRow, _T("备自投方式"), (short)m_pSetpoint->wBZT_Mode, _T(""));
    fData = m_pSetpoint->wBZT_MLSetUh*0.01f;
    AddEditSub(pRow, _T("母联有压定值"), fData, _T("V"));
    fData = m_pSetpoint->wBZT_MLSetUl*0.01f;
    AddEditSub(pRow, _T("母联失压定值"), fData, _T("V"));
    fData = m_pSetpoint->wBZT_SetUh1*0.01f;
    AddEditSub(pRow, _T("1母联有压定值"), fData, _T("V"));
    fData = m_pSetpoint->wBZT_SetUl1*0.01f;
    AddEditSub(pRow, _T("1母联失压定值"), fData, _T("V"));
    fData = m_pSetpoint->wBZT_SetUh2*0.01f;
    AddEditSub(pRow, _T("2母联有压定值"), fData, _T("V"));
    fData = m_pSetpoint->wBZT_SetUl2*0.01f;
    AddEditSub(pRow, _T("2母联失压定值"), fData, _T("V"));
    fData = m_pSetpoint->wBZT_SetI1*0.01f;
    AddEditSub(pRow, _T("1母联无流定值"), fData, _T("A"));
    fData = m_pSetpoint->wBZT_SetI2*0.01f;
    AddEditSub(pRow, _T("2母联无流定值"), fData, _T("A"));
    fData = m_pSetpoint->wBZT_SetTL1*0.01f;
    AddEditSub(pRow, _T("跳1DL时间"), fData, _T("s"));
    fData = m_pSetpoint->wBZT_SetTL2*0.01f;
    AddEditSub(pRow, _T("跳2DL时间"), fData, _T("s"));
    fData = m_pSetpoint->wBZT_SetT*0.01f;
    AddEditSub(pRow, _T("备自投时间"), fData, _T("s"));
    nProIndex++;
    nProIndex++;

    pRow = AddProtectTog(_T("电流I段"), m_Setpoint.wToggle[nProIndex++]);
    fData = m_pSetpoint->wDL1_SetI*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("A"));
    fData = m_pSetpoint->wDL1_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("低压闭锁"), m_pSetpoint->wDL1_TogU);

    pRow = AddProtectTog(_T("电流II段"), m_Setpoint.wToggle[nProIndex++]);
    fData = m_pSetpoint->wDL2_SetI*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("A"));
    fData = m_pSetpoint->wDL2_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("低压闭锁"), m_pSetpoint->wDL2_TogU);

    pRow = AddProtectTog(_T("电流III段"), m_Setpoint.wToggle[nProIndex++]);
    fData = m_pSetpoint->wDL3_SetI*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("A"));
    fData = m_pSetpoint->wDL3_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
    AddTogSub(pRow, _T("低压闭锁"), m_pSetpoint->wDL3_TogU);

    fData = m_pSetpoint->wDL_SetU*0.01f;
    AddRowEdit(_T("电流保护闭锁电压"), fData,_T("V"));

    pRow = AddProtectTog(_T("零序I段"), m_Setpoint.wToggle[nProIndex++]);
    fData = m_pSetpoint->wLX1_SetI*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("A"));
    fData = m_pSetpoint->wLX1_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));

    pRow = AddProtectTog(_T("零序II段"), m_Setpoint.wToggle[nProIndex++]);
    fData = m_pSetpoint->wLX2_SetI*0.01f;
    AddEditSub(pRow, _T("电流定值"), fData, _T("A"));
    fData = m_pSetpoint->wLX2_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));


    pRow = AddProtectTog(_T("低电压"), m_Setpoint.wToggle[nProIndex++]);
    fData = m_pSetpoint->wSY_SetU*0.01f;
    AddEditSub(pRow, _T("电压定值"), fData, _T("V"));
    fData = m_pSetpoint->wSY_SetI*0.01f;
    AddEditSub(pRow, _T("闭锁电流"), fData, _T("A"));
    fData = m_pSetpoint->wSY_SetT*0.01f;
    AddEditSub(pRow, _T("时间定值"), fData, _T("s"));
}

void CMySetpointGridCtrl::Ctrl2Mem(void)
{
    int nPos = 0;
    int nProIndex = 0;
    float fData;

    m_Setpoint.wToggle[nProIndex++] = GetRowCombox(nPos++);
    m_pSetpoint->wBZT_Mode = GetRowEditInt(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_MLSetUh = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_MLSetUl = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetUh1 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetUl1 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetUh2 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetUl2 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetI1 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetI2 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetTL1 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetTL2 = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wBZT_SetT = bcg_round(fData*100);
    nProIndex++;
    nProIndex++;

    m_Setpoint.wToggle[nProIndex++] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wDL1_SetI = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wDL1_SetT = bcg_round(fData*100);
    m_pSetpoint->wDL1_TogU = GetRowCombox(nPos++);

    m_Setpoint.wToggle[nProIndex++] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wDL2_SetI = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wDL2_SetT = bcg_round(fData*100);
    m_pSetpoint->wDL2_TogU = GetRowCombox(nPos++);

    m_Setpoint.wToggle[nProIndex++] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wDL3_SetI = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wDL3_SetT = bcg_round(fData*100);
    m_pSetpoint->wDL3_TogU = GetRowCombox(nPos++);

    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wDL_SetU = bcg_round(fData*100);

    m_Setpoint.wToggle[nProIndex++] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wLX1_SetI = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wLX1_SetT = bcg_round(fData*100);

    m_Setpoint.wToggle[nProIndex++] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wLX2_SetI = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wLX2_SetT = bcg_round(fData*100);

    m_Setpoint.wToggle[nProIndex++] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wSY_SetU = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wSY_SetI = bcg_round(fData*100);
    fData = GetRowEditFloat(nPos++);
    m_pSetpoint->wSY_SetT = bcg_round(fData*100);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDlgSetpoint dialog


CMyDlgSetpoint::CMyDlgSetpoint(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgSetpoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgSetpoint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
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
    ASSERT(m_pSetpoint);
    CWaitCursor wait;
    memcpy(&m_wndGrid.m_Setpoint, m_pSetpoint->m_pMemR, m_pSetpoint->m_nSize);

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
    if(MyMessageBox("本操作将修改设备当前的运行参数,\t\n请确认是否下装?","请注意",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_wndGrid.Ctrl2Mem();
        m_pSetpoint->StoreToDevice(&m_wndGrid.m_Setpoint);
    }
// 	CBCGPDialog::OnOK();
}
