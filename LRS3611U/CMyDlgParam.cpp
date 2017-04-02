// CMyDlgParam.cpp : implementation file
//

#include "stdafx.h"
#include "CMyUnitModbus.h"
#include "CMyUnitDevice.h"
#include "CMyGridCtrl.h"
#include "CMyDlgParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyParamGridCtrl sample class
const CString c_strBaud[3] = 
{
    _T("2400"), _T("4800"), _T("9600")
};

CMyParamGridCtrl::CMyParamGridCtrl()
{
}

CMyParamGridCtrl::~CMyParamGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyParamGridCtrl, CMyGridCtrl)
    //{{AFX_MSG_MAP(CMyParamGridCtrl)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyParamGridCtrl message handlers

int CMyParamGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CMyGridCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_pParamNPS = (tDEVICEPARAM_NPS*)m_Param.wReserved;

    AddCtrl();

    return 0;
}

void CMyParamGridCtrl::AddCtrl(void)
{
    int i=0;
    CStringArray aContent;

    char szDevType[20];
    CString strDevType;
    for(i=0;i<16;i++)
    {
        szDevType[i] = m_Param.wszDeviceType[i]&0xff;
    }
    szDevType[i] = '\0';
    strDevType = szDevType;

    CBCGPGridRow* pRow = CreateNewRow();
    pRow->GetItem(0)->SetValue(_T("设备名称"));
    pRow->GetItem(1)->SetValue((LPCTSTR)strDevType);

    AddRow(pRow, FALSE);

    AddRowEdit(_T("通讯地址"), (int)m_Param.wModbusAddr1, _T(""));

    aContent.RemoveAll();
    for(i=0;i<3;i++)
    {
        aContent.Add(c_strBaud[i]);
    }
    AddRowCombox(_T("波特率"), (int)m_Param.wBaudrate1, aContent, _T(""));

    aContent.RemoveAll();
    aContent.Add(_T("OFF"));
    aContent.Add(_T("ON"));
    AddRowCombox(_T("PT断线检测"), (int)m_pParamNPS->wToggleAlarmPT, aContent, _T(""));
    AddRowCombox(_T("PT电压VV接线"), (int)m_pParamNPS->wModePT, aContent, _T(""));

    AddRowEdit(_T("CT变比"), (int)m_pParamNPS->wScaleCT, _T(""));
    AddRowEdit(_T("PT变比"), (int)m_pParamNPS->wScalePT, _T(""));

    AddRowEdit(_T("主接线类型"), (int)m_pParamNPS->wSLType, _T(""));
    AddRowCombox(_T("开入9为就地"), (int)m_pParamNPS->wDevLocal, aContent, _T(""));
}

void CMyParamGridCtrl::Ctrl2Mem(void)
{
    int nPos = 0;

    _variant_t var;
    CString strTmp;
    CBCGPGridRow* pRow = GetRow(nPos++);
    ASSERT(pRow);
    var = pRow->GetItem(1)->GetValue();
    if(var.vt==VT_BSTR)
    {
        strTmp = (LPCTSTR)(_bstr_t)var;
    }

    int nLen = strTmp.GetLength();
    if(nLen>16) nLen = 16;
    int i = 0;
    for(i=0;i<nLen;i++)
    {
        m_Param.wszDeviceType[i] = strTmp.GetAt(i);
    }
    m_Param.wszDeviceType[i] = 0;

    m_Param.wModbusAddr1 = GetRowEditInt(nPos++);
    m_Param.wBaudrate1 = GetRowCombox(nPos++);

    m_pParamNPS->wToggleAlarmPT = GetRowCombox(nPos++);
    m_pParamNPS->wModePT = GetRowCombox(nPos++);

    m_pParamNPS->wScaleCT = GetRowEditInt(nPos++);
    m_pParamNPS->wScalePT = GetRowEditInt(nPos++);

    m_pParamNPS->wSLType = GetRowEditInt(nPos++);
    m_pParamNPS->wDevLocal = GetRowCombox(nPos++);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDlgParam dialog


CMyDlgParam::CMyDlgParam(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgParam)
	//}}AFX_DATA_INIT
    m_pParam = NULL;
    EnableLayout ();
}


void CMyDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgParam)
	DDX_Control(pDX, IDC_LIST_PARAM, m_wndLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgParam, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgParam message handlers

BOOL CMyDlgParam::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pParam);
    CWaitCursor wait;
    memcpy(&m_wndGrid.m_Param, m_pParam->m_pMemR, m_pParam->m_nSize);
    
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

void CMyDlgParam::OnOK() 
{
	// TODO: Add extra validation here
    if(MyMessageBox("本操作将修改设备当前的运行参数,\t\n请确认是否下装?","请注意",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_wndGrid.Ctrl2Mem();
        m_pParam->StoreToDevice(&m_wndGrid.m_Param);
    }

// 	CBCGPDialog::OnOK();
}
