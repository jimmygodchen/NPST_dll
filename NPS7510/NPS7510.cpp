// NPS7510.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "NPS7510.h"
#include "CMyNPS7510Dlg.h"
#include "CMyDlgParam.h"
#include "CMyDlgRegulate.h"
#include "CMyDlgSetpoint.h"
#include "CMyDlgYC.h"
#include "CMyOpenList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE NPS7510DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("NPS7510.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(NPS7510DLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(NPS7510DLL);
        CMyUnit::RegisterClass(_T("NPS7510"), RUNTIME_CLASS(CMyUnitNPS7510));
        CMyData::RegisterClass(_T("NPSParam"), RUNTIME_CLASS(CMyDataNPSParam),TRUE);
        CMyData::RegisterClass(_T("NPSRegulate"), RUNTIME_CLASS(CMyDataNPSRegulate),TRUE);
        CMyData::RegisterClass(_T("NPSSetpoint"), RUNTIME_CLASS(CMyDataNPSSetpoint),TRUE);
        CMyData::RegisterClass(_T("NPSYC"), RUNTIME_CLASS(CMyDataNPSYC),TRUE);
        CMyData::RegisterClass(_T("NPSOPList"),RUNTIME_CLASS(CMyDataOPList));
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("NPS7510.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(NPS7510DLL);
	}
	return 1;   // ok
}

#define LOGADDR_DEVICETIME		0x0000		//RW;
#define LOGADDR_DEVICEINFO		0x0007		//R;
#define LOGADDR_ANALOGDATA		0x0100		//R;
#define LOGADDR_ANALOGDATAEXT	0x0200		//R;
#define LOGADDR_ANALOGWAVE		0x0300		//R;
#define LOGADDR_DFTDATASET		0x0900		//R;
#define LOGADDR_CONTROLOUT		0x0a00		//RW;
#define LOGADDR_DEVICEPARAM		0x0b00		//RW;
#define LOGADDR_DEVICEINPARAM	0x0c00		//RW;
#define LOGADDR_DEVICEDCPARAM	0x1100		//RW;
#define LOGADDR_DEVICEREGULATE	0x1300		//RW;
#define LOGADDR_DEVICESETPOINT	0x1400		//RW;
#define LOGADDR_DEVICEDRW		0x1600		//RW;
#define LOGADDR_DEVICELAD		0x1800		//RW;
#define LOGADDR_EVENTTABLE		0x1a00		//R;
#define LOGADDR_WAVERECORD		0x2000		//R;

#define CONTROLOUT_INITDEVICE	0x0000		//初始化设备;
#define CONTROLOUT_RESETDEVICE	0x0001		//复归信号;
#define CONTROLOUT_FREEZEWAVE	0x0002		//冻结故障录波;
#define CONTROLOUT_ADJUST   	0x0003		//校正;
#define CONTROLOUT_KH01			0x0010		//KH01;
#define CONTROLOUT_KH02			0x0011		//KH02;
#define CONTROLOUT_KH03			0x0012		//KH03;
#define CONTROLOUT_KH04			0x0013		//KH04;
#define CONTROLOUT_KH05			0x0014		//KH05;
#define CONTROLOUT_KH06			0x0015		//KH06;
#define CONTROLOUT_KH07			0x0016		//KH07;
#define CONTROLOUT_KH08			0x0017		//KH08;
#define CONTROLOUT_KH09			0x0018		//KH09;
#define CONTROLOUT_KH10			0x0019		//KH10;
#define CONTROLOUT_KH11			0x001a		//KH11;
#define CONTROLOUT_KH12			0x001b		//KH12;
#define CONTROLOUT_KH13			0x001c		//KH13;
#define CONTROLOUT_KH14			0x001d		//KH14;
#define CONTROLOUT_KH15			0x001e		//KH15;
#define CONTROLOUT_KH16			0x001f		//KH16;
#define CONTROLOUT_KH17			0x0020		//KH17;
#define CONTROLOUT_KH18			0x0021		//KH18;
#define CONTROLOUT_KH19			0x0022		//KH19;
#define CONTROLOUT_KH20			0x0023		//KH20;
#define CONTROLOUT_KH21			0x0024		//KH21;
#define CONTROLOUT_KH22			0x0025		//KH22;
#define CONTROLOUT_KH23			0x0026		//KH23;
#define CONTROLOUT_KH24			0x0027		//KH24;
#define CONTROLOUT_KH25			0x0028		//KH25;
#define CONTROLOUT_KH26			0x0029		//KH26;
#define CONTROLOUT_KH27			0x002a		//KH27;
#define CONTROLOUT_KH28			0x002b		//KH28;
#define CONTROLOUT_KH29			0x002c		//KH29;
#define CONTROLOUT_KH30			0x002d		//KH30;
#define CONTROLOUT_KH31			0x002e		//KH31;
#define CONTROLOUT_KH32			0x002f		//KH32;

typedef struct
{
    WORD wDeviceType;					// 设备类型代码
    WORD wSwitchStatus1;				// 开关量状态 0~15
    WORD wSwitchStatus2;				// 开关量状态16~31
    WORD wNumPwrup;						// 启动次数 Number of Power ups
    WORD wWrmStr;						// 热启次数 Number of Warm Starts
    WORD wDeviceStatus1;				// 自检信息
    WORD wDeviceStatus2;
    WORD wDeviceStatus3;
    WORD wDeviceStatus4;
    WORD wExtID;
    WORD wSelfTestMain;					// 主存储器自检信息
    WORD wSelfTestSub;					// 从存储器自检信息
    WORD wCountAll;
    WORD wCountEventTable;
    WORD wCountWaveRecord;
    WORD wCountDeviceParam;
    WORD wCountDeviceRegulate;
    WORD wCountDeviceSetpoint;
    WORD wMainVersion;
    WORD wSubVersion;
    WORD wLCDHeigh;
    WORD wLCDWidth;
    // 	WORD wReserved;
}DEVICEINFO;

typedef struct
{
    WORD wDataIa;
    WORD wDataIb;
    WORD wDataIc;
    WORD wDataIA;
    WORD wDataIB;
    WORD wDataIC;
    WORD wDataUa;
    WORD wDataUb;
    WORD wDataUc;
    WORD wDataUab;
    WORD wDataUbc;
    WORD wDataUca;
    WORD wData3I0;
    WORD wDataF;
    short nDataP;
    short nDataQ;
    short nDataPF;
}ANALOGDATA;


CMyCRC16 g_crc16(0x8005,TRUE);

//---------------------------------------------- CMyDataNPSParam -----------
IMPLEMENT_SERIAL(CMyDataNPSParam,CMyDataOperate,0)

CMyDataNPSParam::CMyDataNPSParam():CMyDataOperate()
{
    m_bOK = FALSE;
    memset(&m_deviceParamR,0,sizeof(m_deviceParamR));
    memset(&m_deviceParamW,0,sizeof(m_deviceParamW));
}

void CMyDataNPSParam::RefreshData(DEVICEPARAM& DeviceParam)
{
    m_deviceParamR = DeviceParam;
    m_bOK = TRUE;
    IncrementUpdateID();
}

void CMyDataNPSParam::StoreToDevice(DEVICEPARAM& DeviceParam)
{
    m_deviceParamW = DeviceParam;
    m_OperateCode = 0xff;
    IncrementUpdateID();
}

BOOL CMyDataNPSParam::ExeOperate(void)
{
    if(m_bOK)
    {
        ASSERT(m_pParentUnit);
        ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitNPS7510)));
        ((CMyUnitNPS7510*)m_pParentUnit)->OnEditDeviceParam(this);
    }
    return FALSE;
}

//---------------------------------------------- CMyDataNPSRegulate -----------
IMPLEMENT_SERIAL(CMyDataNPSRegulate,CMyDataOperate,0)

CMyDataNPSRegulate::CMyDataNPSRegulate():CMyDataOperate()
{
    m_bOK = FALSE;
    memset(&m_RegulateR,0,sizeof(m_RegulateR));
    memset(&m_RegulateW,0,sizeof(m_RegulateW));
}

void CMyDataNPSRegulate::RefreshData(REGULATESET& Regulate)
{
    m_RegulateR = Regulate;
    m_bOK = TRUE;
    IncrementUpdateID();
}

void CMyDataNPSRegulate::StoreToDevice(REGULATESET& Regulate)
{
    m_RegulateW = Regulate;
    m_OperateCode = 0xff;
    IncrementUpdateID();
}

BOOL CMyDataNPSRegulate::ExeOperate(void)
{
    if(m_bOK)
    {
        ASSERT(m_pParentUnit);
        ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitNPS7510)));
        ((CMyUnitNPS7510*)m_pParentUnit)->OnEditRegulate(this);
    }
    return FALSE;
}

//---------------------------------------------- CMyDataNPSSetpoint -----------
IMPLEMENT_SERIAL(CMyDataNPSSetpoint,CMyDataOperate,0)

CMyDataNPSSetpoint::CMyDataNPSSetpoint():CMyDataOperate()
{
    m_bOK = FALSE;
    memset(&m_SetpointR,0,sizeof(m_SetpointR));
    memset(&m_SetpointW,0,sizeof(m_SetpointW));
}

void CMyDataNPSSetpoint::RefreshData(DEVICESETPOINT& Setpoint)
{
    m_SetpointR = Setpoint;
    m_bOK = TRUE;
    IncrementUpdateID();
}

void CMyDataNPSSetpoint::StoreToDevice(DEVICESETPOINT& Setpoint)
{
    m_SetpointW = Setpoint;
    m_OperateCode = 0xff;
    IncrementUpdateID();
}

BOOL CMyDataNPSSetpoint::ExeOperate(void)
{
    if(m_bOK)
    {
        ASSERT(m_pParentUnit);
        ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitNPS7510)));
        ((CMyUnitNPS7510*)m_pParentUnit)->OnEditSetpoint(this);
    }
    return FALSE;
}

//---------------------------------------------- CMyDataNPSYC -----------
IMPLEMENT_SERIAL(CMyDataNPSYC,CMyDataOperate,0)

CMyDataNPSYC::CMyDataNPSYC():CMyDataOperate()
{
}

BOOL CMyDataNPSYC::ExeOperate(void)
{
    ASSERT(m_pParentUnit);
    ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitNPS7510)));
    ((CMyUnitNPS7510*)m_pParentUnit)->OnExcuteYC(this);
    return FALSE;
}

//------------------------------- CMyDataOPList -----------------------------------
IMPLEMENT_SERIAL(CMyDataOPList,CMyDataOperate,0)

CMyDataOPList::CMyDataOPList():CMyDataOperate()
{
    m_nOPIndex = 0;
}

// void CMyDataOPList::SerializeDynInfo(CArchive& ar,int nDynInfoMode)
// {
//     CMyDataOperate::SerializeDynInfo(ar,nDynInfoMode);
//     int nSize = m_arOPList.GetSize();
//     if(ar.IsStoring())
//     {
//         ar << m_nOPIndex;
//         ar << nSize;
//         for(int i=0;i<nSize;i++)
//         {
//             ar << m_arOPList[i].strName;
//             ar << m_arOPList[i].nIndex;
//         }
//     }
//     else
//     {
//         ar >> m_nOPIndex;
//         ar >> nSize;
//         m_arOPList.RemoveAll();
//         m_arOPList.SetSize(nSize);
//         for(int i=0;i<nSize;i++)
//         {
//             ar >> m_arOPList[i].strName;
//             ar >> m_arOPList[i].nIndex;
//         }
//     }
// }

void CMyDataOPList::RefreshData(CArray<OPList,OPList>& arOpList)
{
    int nSize = arOpList.GetSize();
    m_arOPList.RemoveAll();
    for(int i=0;i<nSize;i++)
    {
        m_arOPList.Add(arOpList[i]);
    }
    IncrementUpdateID();
}

void CMyDataOPList::SndCmd(int nOPIndex,BYTE Cmd/*=0xff*/)
{
    m_nOPIndex = nOPIndex;
    m_OperateCode = Cmd;
    IncrementUpdateID();
}

BOOL CMyDataOPList::ExeOperate(void)
{
    ASSERT(m_pParentUnit);
    ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitNPS7510)));
    ((CMyUnitNPS7510*)m_pParentUnit)->OnOpenList(this);
    return FALSE;
}

//---------------------------------------------- CMyUnitNPS7510 -----------------------
IMPLEMENT_SERIAL(CMyUnitNPS7510,CMyUnit,0)

CMyUnitNPS7510::CMyUnitNPS7510():CMyUnit()
{
    m_nAddr = 1;
    m_nTimeout = 1000;

    m_bInfoOK = FALSE;
    m_bTimeSyn = FALSE;
    m_bParamOK = FALSE;
    m_bRegulateOK = FALSE;
    m_bSetpointOK = FALSE;
    m_bWaveRecordListOK = FALSE;

//     m_wCountInfo = 0;
    m_wCountParam = 0;
    m_wCountParamOld = 0;
    m_wCountRegulate = 0;
    m_wCountRegulateOld = 0;
    m_wCountSetpoint = 0;
    m_wCountSetpointOld = 0;
    m_wCountEvent = 0;
    m_wCountEventOld = 0;
    m_wCountWaveRecord = 0;
    m_wCountWaveRecordOld = 0;
}

CMyUnitNPS7510::~CMyUnitNPS7510()
{
}

void CMyUnitNPS7510::Serialize(CArchive& ar)
{
    CMyUnit::Serialize(ar);
    if(ar.IsStoring())
    {
        ar << m_nAddr;
        ar << m_nTimeout;
    }
    else
    {
        ar >> m_nAddr;
        ar >> m_nTimeout;
    }
}

BOOL CMyUnitNPS7510::OnAttrib(CBCGPPropertySheet& sheet)
{
    HINSTANCE hInstOld = AfxGetResourceHandle();
    AfxSetResourceHandle(NPS7510DLL.hModule);
    
    CMyNPS7510Dlg pageNPS;
    pageNPS.m_nAddr = m_nAddr;
    pageNPS.m_nTimeout = m_nTimeout;
    sheet.AddPage(&pageNPS);
    
    if(CMyUnit::OnAttrib(sheet))
    {
        m_nAddr = pageNPS.m_nAddr;
        m_nTimeout = pageNPS.m_nTimeout;

        AfxSetResourceHandle(hInstOld);
        return TRUE;
    }
    
    AfxSetResourceHandle(hInstOld);
    
    return FALSE;
}

void CMyUnitNPS7510::ExchangeComData(COMCONTROL* pCC)
{
    int i;
    if(!m_bInfoOK) { ReceiveInfo(pCC); return; }
    if(!m_bTimeSyn) { TimeSyn(pCC); return;}
    if(!m_bParamOK) { ReceiveParam(pCC); return; }
    if(!m_bRegulateOK) { ReceiveRegulate(pCC); return; }
    if(!m_bSetpointOK) { ReceiveSetpoint(pCC); return; }
    if(!m_bWaveRecordListOK) { ReceiveWaveRecordHeadList(pCC); return; }
    if(m_wCountEvent!=m_wCountEventOld) { ReceiveEventTable(pCC); return; }

    if(m_wCountParam!=m_wCountParamOld)
    {
         ReceiveParam(pCC);
         m_wCountParamOld = m_wCountParam;
         return;
    }

    if(m_wCountRegulate!=m_wCountRegulateOld)
    {
        ReceiveRegulate(pCC);
        m_wCountRegulateOld = m_wCountRegulate;
        return;
    }

    if(m_wCountSetpoint!=m_wCountSetpointOld)
    {
        ReceiveSetpoint(pCC);
        m_wCountSetpointOld = m_wCountSetpoint;
        return;
    }

    if(m_wCountWaveRecordOld!=m_wCountWaveRecord)
    {
        ReceiveWaveRecordHeadList(pCC);
        WORD wCount = m_wCountWaveRecord - m_wCountWaveRecordOld;
        if(wCount>1) m_wCountWaveRecordOld = m_wCountWaveRecord;
        else
        {
            if(ReceiveWave(pCC, m_wCountWaveRecordOld))
            {
                m_wCountWaveRecordOld++;
            }
        }
        return;
    }

    if(m_pWaveRecordList && m_pWaveRecordList->GetOperateCode())
    {
        int nWaveNo = m_pWaveRecordList->m_arOPList[m_pWaveRecordList->m_nOPIndex].nIndex;
        ReceiveWave(pCC, nWaveNo);
        m_pWaveRecordList->EndOperate();
    }

    if(m_pParam && m_pParam->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC,LOGADDR_DEVICEPARAM,sizeof(DEVICEPARAM)/sizeof(short),(WORD*)&(m_pParam->m_deviceParamW));
        m_pParam->EndOperate();
    }

    if(m_pRegulate && m_pRegulate->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC,LOGADDR_DEVICEREGULATE,sizeof(REGULATESET)/sizeof(short),(WORD*)&(m_pRegulate->m_RegulateW));
        m_pRegulate->EndOperate();
    }

    if(m_pSetpoint && m_pSetpoint->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC,LOGADDR_DEVICESETPOINT,sizeof(DEVICESETPOINT)/sizeof(short),(WORD*)&(m_pSetpoint->m_SetpointW));
        m_pSetpoint->EndOperate();
    }

    for(i=0;i<6;i++)
    {
        if(m_pYC[i])
        {
            BYTE Code = m_pYC[i]->GetOperateCode();
            WORD wCode = Code*0x0101;
            if(wCode)
            {
                MODBUS_Write(pCC,LOGADDR_CONTROLOUT+CONTROLOUT_KH01+i,1,&wCode);
                m_pYC[i]->EndOperate();
            }
        }
    }

    if(m_pOP[0] && m_pOP[0]->GetOperateCode()==0xff)
    {
        WORD wCode = 0xaaaa;
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_INITDEVICE, 1, &wCode);
        m_pOP[0]->EndOperate();
    }

    if(m_pOP[1] && m_pOP[1]->GetOperateCode()==0xff)
    {
        WORD wCode = 0xaaaa;
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_RESETDEVICE, 1, &wCode);
        m_pOP[1]->EndOperate();
    }

    if(m_pOP[2] && m_pOP[2]->GetOperateCode()==0xff)
    {
        WORD wCode = 0xaaaa;
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_FREEZEWAVE, 1, &wCode);
        m_pOP[2]->EndOperate();
    }

    if(m_pOP[3] && m_pOP[3]->GetOperateCode()==0xff)
    {
        WORD wCode = 0xaaaa;
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_ADJUST, 1, &wCode);
        m_pOP[3]->EndOperate();
    }

    if(m_pOP[4] && m_pOP[4]->GetOperateCode()==0xff)
    {
//         WORD wCode = 0xaaaa;
//         MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_ADJUST, 1, &wCode);
        TimeSyn(pCC);
        m_pOP[4]->EndOperate();
    }

    int nTask = m_commdispatch.GetActiveTask();
    switch(nTask)
    {
    case 0: ReceiveInfo(pCC); break;
    case 1: ReceiveAnalog(pCC); break;
    default: break;
    }

}

BOOL CMyUnitNPS7510::OnCreate(void)
{
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ia"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ib"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ic"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("IA"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("IB"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("IC"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ua"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ub"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Uc"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Uab"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ubc"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Uca"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("3I0"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Freq"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("P"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Q"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("PF"));

    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI01"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI02"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI03"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI04"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI05"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI06"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI07"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI08"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI09"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI10"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI11"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI12"));

    AddDataFactory(RUNTIME_CLASS(CMyDataNPSYC), _T("YC1"));
    AddDataFactory(RUNTIME_CLASS(CMyDataNPSYC), _T("YC2"));
    AddDataFactory(RUNTIME_CLASS(CMyDataNPSYC), _T("YC3"));
    AddDataFactory(RUNTIME_CLASS(CMyDataNPSYC), _T("YC4"));
    AddDataFactory(RUNTIME_CLASS(CMyDataNPSYC), _T("YC5"));
    AddDataFactory(RUNTIME_CLASS(CMyDataNPSYC), _T("YC6"));

    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("InitDevice"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("Reset"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("FreezeWave"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("Adjust"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("TimeSyn"));

    AddDataFactory(RUNTIME_CLASS(CMyDataNPSParam), _T("Param"));
    AddDataFactory(RUNTIME_CLASS(CMyDataNPSRegulate), _T("Regulate"));
    AddDataFactory(RUNTIME_CLASS(CMyDataNPSSetpoint), _T("Setpoint"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOPList), _T("WaveRecordList"));

    return TRUE;
}

BOOL CMyUnitNPS7510::OnCreateData(CMyData* pData)
{
    if(pData->m_strField==_T("Ia")) ((CMyDataFloat*)pData)->Initialize(_T("A相测量电流"), _T("A"),2);
    else if(pData->m_strField==_T("Ib")) ((CMyDataFloat*)pData)->Initialize(_T("B相测量电流"), _T("A"),2);
    else if(pData->m_strField==_T("Ic")) ((CMyDataFloat*)pData)->Initialize(_T("C相测量电流"), _T("A"),2);
    else if(pData->m_strField==_T("IA")) ((CMyDataFloat*)pData)->Initialize(_T("A相电流"), _T("A"),2);
    else if(pData->m_strField==_T("IB")) ((CMyDataFloat*)pData)->Initialize(_T("B相电流"), _T("A"),2);
    else if(pData->m_strField==_T("IC")) ((CMyDataFloat*)pData)->Initialize(_T("C相电流"), _T("A"),2);
    else if(pData->m_strField==_T("Ua")) ((CMyDataFloat*)pData)->Initialize(_T("A相电压"), _T("V"),2);
    else if(pData->m_strField==_T("Ub")) ((CMyDataFloat*)pData)->Initialize(_T("B相电压"), _T("V"),2);
    else if(pData->m_strField==_T("Uc")) ((CMyDataFloat*)pData)->Initialize(_T("C相电压"), _T("V"),2);
    else if(pData->m_strField==_T("Uab")) ((CMyDataFloat*)pData)->Initialize(_T("AB线电压"), _T("V"),2);
    else if(pData->m_strField==_T("Ubc")) ((CMyDataFloat*)pData)->Initialize(_T("BC线电压"), _T("V"),2);
    else if(pData->m_strField==_T("Uca")) ((CMyDataFloat*)pData)->Initialize(_T("CA线电压"), _T("V"),2);
    else if(pData->m_strField==_T("3I0")) ((CMyDataFloat*)pData)->Initialize(_T("零序电流"), _T("A"),2);
    else if(pData->m_strField==_T("Freq")) ((CMyDataFloat*)pData)->Initialize(_T("频率"), _T("Hz"),2);
    else if(pData->m_strField==_T("P")) ((CMyDataFloat*)pData)->Initialize(_T("有功功率"), _T("W"),2);
    else if(pData->m_strField==_T("Q")) ((CMyDataFloat*)pData)->Initialize(_T("无功功率"), _T("Var"),2);
    else if(pData->m_strField==_T("PF")) ((CMyDataFloat*)pData)->Initialize(_T("功率因数"), _T(""),3);

    else if(pData->m_strField==_T("BI01")) ((CMyDataBin*)pData)->Initialize(_T("BI01"));
    else if(pData->m_strField==_T("BI02")) ((CMyDataBin*)pData)->Initialize(_T("BI02"));
    else if(pData->m_strField==_T("BI03")) ((CMyDataBin*)pData)->Initialize(_T("BI03"));
    else if(pData->m_strField==_T("BI04")) ((CMyDataBin*)pData)->Initialize(_T("BI04"));
    else if(pData->m_strField==_T("BI05")) ((CMyDataBin*)pData)->Initialize(_T("BI05"));
    else if(pData->m_strField==_T("BI06")) ((CMyDataBin*)pData)->Initialize(_T("BI06"));
    else if(pData->m_strField==_T("BI07")) ((CMyDataBin*)pData)->Initialize(_T("BI07"));
    else if(pData->m_strField==_T("BI08")) ((CMyDataBin*)pData)->Initialize(_T("BI08"));
    else if(pData->m_strField==_T("BI09")) ((CMyDataBin*)pData)->Initialize(_T("BI09"));
    else if(pData->m_strField==_T("BI10")) ((CMyDataBin*)pData)->Initialize(_T("BI10"));
    else if(pData->m_strField==_T("BI11")) ((CMyDataBin*)pData)->Initialize(_T("BI11"));
    else if(pData->m_strField==_T("BI12")) ((CMyDataBin*)pData)->Initialize(_T("BI12"));

    else if(pData->m_strField==_T("YC1")) ((CMyDataOperate*)pData)->Initialize(_T("遥跳"));
    else if(pData->m_strField==_T("YC2")) ((CMyDataOperate*)pData)->Initialize(_T("跳闸"));
    else if(pData->m_strField==_T("YC3")) ((CMyDataOperate*)pData)->Initialize(_T("遥合"));
    else if(pData->m_strField==_T("YC4")) ((CMyDataOperate*)pData)->Initialize(_T("合闸"));
    else if(pData->m_strField==_T("YC5")) ((CMyDataOperate*)pData)->Initialize(_T("故障"));
    else if(pData->m_strField==_T("YC6")) ((CMyDataOperate*)pData)->Initialize(_T("告警"));

    else if(pData->m_strField==_T("InitDevice")) ((CMyDataOperate*)pData)->Initialize(_T("设备初始化"));
    else if(pData->m_strField==_T("Reset")) ((CMyDataOperate*)pData)->Initialize(_T("设备复归"));
    else if(pData->m_strField==_T("FreezeWave")) ((CMyDataOperate*)pData)->Initialize(_T("手动录波"));
    else if(pData->m_strField==_T("Adjust")) ((CMyDataOperate*)pData)->Initialize(_T("校正"));
    else if(pData->m_strField==_T("TimeSyn")) ((CMyDataOperate*)pData)->Initialize(_T("校时"));

    else if(pData->m_strField==_T("Param")) ((CMyDataNPSParam*)pData)->Initialize(_T("编辑参数"));
    else if(pData->m_strField==_T("Regulate")) ((CMyDataNPSParam*)pData)->Initialize(_T("编辑校正系数"));
    else if(pData->m_strField==_T("Setpoint")) ((CMyDataNPSSetpoint*)pData)->Initialize(_T("编辑保护定值"));
    else if(pData->m_strField=="WaveRecordList") ((CMyDataOPList*)pData)->Initialize("故障录波列表");

    return TRUE;
}

void CMyUnitNPS7510::OnPortOpen(void)
{
    m_pIa = (CMyDataFloat*)GetData(_T("Ia"));
    m_pIb = (CMyDataFloat*)GetData(_T("Ib"));
    m_pIc = (CMyDataFloat*)GetData(_T("Ic"));
    m_pIA = (CMyDataFloat*)GetData(_T("IA"));
    m_pIB = (CMyDataFloat*)GetData(_T("IB"));
    m_pIC = (CMyDataFloat*)GetData(_T("IC"));
    m_pUa = (CMyDataFloat*)GetData(_T("Ua"));
    m_pUb = (CMyDataFloat*)GetData(_T("Ub"));
    m_pUc = (CMyDataFloat*)GetData(_T("Uc"));
    m_pUab = (CMyDataFloat*)GetData(_T("Uab"));
    m_pUbc = (CMyDataFloat*)GetData(_T("Ubc"));
    m_pUca = (CMyDataFloat*)GetData(_T("Uca"));
    m_p3I0 = (CMyDataFloat*)GetData(_T("3I0"));
    m_pF = (CMyDataFloat*)GetData(_T("Freq"));
    m_pP = (CMyDataFloat*)GetData(_T("P"));
    m_pQ = (CMyDataFloat*)GetData(_T("Q"));
    m_pPF = (CMyDataFloat*)GetData(_T("PF"));

    m_pBi[0] = (CMyDataBin*)GetData(_T("BI01"));
    m_pBi[1] = (CMyDataBin*)GetData(_T("BI02"));
    m_pBi[2] = (CMyDataBin*)GetData(_T("BI03"));
    m_pBi[3] = (CMyDataBin*)GetData(_T("BI04"));
    m_pBi[4] = (CMyDataBin*)GetData(_T("BI05"));
    m_pBi[5] = (CMyDataBin*)GetData(_T("BI06"));
    m_pBi[6] = (CMyDataBin*)GetData(_T("BI07"));
    m_pBi[7] = (CMyDataBin*)GetData(_T("BI08"));
    m_pBi[8] = (CMyDataBin*)GetData(_T("BI09"));
    m_pBi[9] = (CMyDataBin*)GetData(_T("BI10"));
    m_pBi[10] = (CMyDataBin*)GetData(_T("BI11"));
    m_pBi[11] = (CMyDataBin*)GetData(_T("BI12"));

    m_pYC[0] = (CMyDataNPSYC*)GetData(_T("YC1"));
    m_pYC[1] = (CMyDataNPSYC*)GetData(_T("YC2"));
    m_pYC[2] = (CMyDataNPSYC*)GetData(_T("YC3"));
    m_pYC[3] = (CMyDataNPSYC*)GetData(_T("YC4"));
    m_pYC[4] = (CMyDataNPSYC*)GetData(_T("YC5"));
    m_pYC[5] = (CMyDataNPSYC*)GetData(_T("YC6"));

    m_pOP[0] = (CMyDataOperate*)GetData(_T("InitDevice"));
    m_pOP[1] = (CMyDataOperate*)GetData(_T("Reset"));
    m_pOP[2] = (CMyDataOperate*)GetData(_T("FreezeWave"));
    m_pOP[3] = (CMyDataOperate*)GetData(_T("Adjust"));
    m_pOP[4] = (CMyDataOperate*)GetData(_T("TimeSyn"));

    m_pParam = (CMyDataNPSParam*)GetData(_T("Param"));
    m_pRegulate = (CMyDataNPSRegulate*)GetData(_T("Regulate"));
    m_pSetpoint = (CMyDataNPSSetpoint*)GetData(_T("Setpoint"));
    m_pWaveRecordList = (CMyDataOPList*)GetData("WaveRecordList");

    m_commdispatch.AddTask(5);         // 设备信息
    m_commdispatch.AddTask(5);         // 模拟量
}

int CMyUnitNPS7510::ReadCom(COMCONTROL* pCC, BYTE* pBuff, int nLen)
{
    int nLenRcv = 0;
    DWORD dwTimeold = timeGetTime();
    DWORD dwTimeNow = dwTimeold;
    while((dwTimeNow - dwTimeold)<m_nTimeout)
    {
        int nLenRcved = pCCPort->ReadCom(pBuff+nLenRcv, nLen-nLenRcv);
        nLenRcv += nLenRcved;
        Sleep(20);
        if(nLenRcv>=nLen) break;
        dwTimeNow = timeGetTime();
    }
    return nLenRcv;
}

BOOL CMyUnitNPS7510::MODBUS_Read(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord)
{
    BYTE* pTX = pCCTX;
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x03;
    *pTX++ = BYTE(wBaseAddress>>8);
    *pTX++ = BYTE(wBaseAddress&0xff);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    WORD wCRC = 0xffff;
    g_crc16.CalculateCRC(pCCTX,pTX-pCCTX,wCRC);
    *pTX++ = BYTE(wCRC&0xff);
    *pTX++ = BYTE(wCRC>>8);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);
    // 	Sleep(100);
    int nLength = wCountWord*2+((wCountWord<=125)?5:6);
    int nLengthRead = 0;
    
    Sleep(200);
//     nLengthRead = pCCPort->ReadCom(pCCRX,nLength);
    nLengthRead = ReadCom(pCC, pCCRX, nLength);

    if(nLengthRead<nLength)
    {
        AddEvent(_T("通信超时!"));
        return FALSE;
    }
    if(pCCRX[0]!=(BYTE)m_nAddr)
    { 
        AddEvent(_T("通信地址出错!"));
        return FALSE; 
    }
    
    if(pCCRX[1]!=0x03)
    {
        AddEvent(_T("功能码应答出错!"));
        return FALSE; 
    }

    wCRC = 0xffff;
    g_crc16.CalculateCRC(pCCRX,nLength,wCRC);
    if(wCRC!=0)
    {
        AddEvent(_T("校验和出错!"));
        return FALSE;
    }
    
    BYTE* pRX = (wCountWord<=125)?(pCCRX+3):(pCCRX+4);
    for(WORD i=0;i<wCountWord;i++)
    {
        BYTE Temp;
        Temp = *pRX;
        *pRX++ = *(pRX+1);
        *pRX++ = Temp;
    }
    return TRUE;
}

BOOL CMyUnitNPS7510::MODBUS_Write(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord,WORD* pData)
{
    BYTE* pTX = pCCTX;
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x10;
    *pTX++ = BYTE(wBaseAddress>>8);
    *pTX++ = BYTE(wBaseAddress&0xff);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    if(wCountWord<=125)
    {
        *pTX++ = BYTE(wCountWord*2);
    }
    else
    {
        *pTX++ = BYTE((wCountWord*2)&0xff);
        *pTX++ = BYTE((wCountWord*2)>>8);
    }
    for(WORD i=0;i<wCountWord;i++)
    {
        *pTX++ = *pData>>8;
        *pTX++ = *pData&0xff;
        pData++;
    }
    WORD wCRC = 0xffff;
    g_crc16.CalculateCRC(pCCTX,pTX-pCCTX,wCRC);
    *pTX++ = BYTE(wCRC&0xff);
    *pTX++ = BYTE(wCRC>>8);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);

    Sleep(300);

    if(m_nAddr==0) return TRUE;
    if(pCCPort->ReadCom(pCCRX,8)<8)
    {
        AddEvent(_T("通信超时!"));
        return FALSE;
    }
    
    if(pCCRX[0]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return FALSE;
    }
    
    if(pCCRX[1]!=0x10)
    {
        AddEvent(_T("功能码应答出错!"));
        return FALSE;
    }

    wCRC = 0xffff;
    g_crc16.CalculateCRC(pCCRX,8,wCRC);
    if(wCRC!=0)
    {
        AddEvent(_T("校验和出错!"));
        return FALSE;
    }
    return TRUE;
}

void CMyUnitNPS7510::ReceiveInfo(COMCONTROL* pCC)
{
    int i;

    if(MODBUS_Read(pCC, LOGADDR_DEVICEINFO, (sizeof(DEVICEINFO)/sizeof(WORD)))==FALSE) return;
    DEVICEINFO deviceInfo;
    memcpy(&deviceInfo, pCCRX+3, sizeof(DEVICEINFO));

    if(deviceInfo.wDeviceType!=7510)
    {
        AddEvent(_T("设备类型不匹配!"));
        return;
    }

    WORD wMask = 0x01;
    for(i=0; i<12; i++, wMask = wMask<<1)
    {
        if(m_pBi[i]) m_pBi[i]->RefreshData((deviceInfo.wSwitchStatus1&wMask)?1:0);
    }

    if(m_bInfoOK==FALSE)
    {
        m_wCountParam = m_wCountParamOld = deviceInfo.wCountDeviceParam;
        m_wCountRegulate = m_wCountRegulateOld = deviceInfo.wCountDeviceSetpoint;
        m_wCountSetpoint = m_wCountSetpointOld = deviceInfo.wCountDeviceRegulate;
        m_wCountEvent = m_wCountEventOld = deviceInfo.wCountEventTable;
        m_wCountWaveRecord = m_wCountWaveRecordOld = deviceInfo.wCountWaveRecord;
    }
    else
    {
        m_wCountParam = deviceInfo.wCountDeviceParam;
        m_wCountRegulate = deviceInfo.wCountDeviceRegulate;
        m_wCountSetpoint = deviceInfo.wCountDeviceSetpoint;
        m_wCountEvent = deviceInfo.wCountEventTable;
        m_wCountWaveRecord = deviceInfo.wCountWaveRecord;
    }

    m_bInfoOK = TRUE;
}

void CMyUnitNPS7510::ReceiveParam(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_DEVICEPARAM, (sizeof(DEVICEPARAM)/sizeof(WORD)))==FALSE) return;
    DEVICEPARAM deviceParam;
    DEVICEPARAM_NPS* pParamNPS = (DEVICEPARAM_NPS*)deviceParam.wReserved;
    memcpy(&deviceParam, pCCRX+3, sizeof(DEVICEPARAM));

    if(m_pParam) m_pParam->RefreshData(deviceParam);

    m_bParamOK = TRUE;
}

void CMyUnitNPS7510::ReceiveRegulate(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_DEVICEREGULATE, (sizeof(REGULATESET)/sizeof(WORD)))==FALSE) return;
    REGULATESET ReuglateSet;
    memcpy(&ReuglateSet, pCCRX+3, sizeof(REGULATESET));

    if(m_pRegulate) m_pRegulate->RefreshData(ReuglateSet);

    m_bRegulateOK = TRUE;
}

void CMyUnitNPS7510::ReceiveSetpoint(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_DEVICESETPOINT, (sizeof(DEVICESETPOINT)/sizeof(WORD)))==FALSE) return;
    DEVICESETPOINT Setpoint;
    memcpy(&Setpoint, pCCRX+3, sizeof(DEVICESETPOINT));

    if(m_pSetpoint) m_pSetpoint->RefreshData(Setpoint);
    
    m_bSetpointOK = TRUE;

}

void CMyUnitNPS7510::ReceiveAnalog(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_ANALOGDATA, (sizeof(ANALOGDATA)/sizeof(WORD)))==FALSE) return;
    ANALOGDATA Analog;
    memcpy(&Analog, pCCRX+3, sizeof(ANALOGDATA));

    if(m_pIa) m_pIa->RefreshData(Analog.wDataIa*0.002f);             // Analog.wDataIa*6.0000
    if(m_pIb) m_pIb->RefreshData(Analog.wDataIb*0.002f);
    if(m_pIc) m_pIc->RefreshData(Analog.wDataIc*0.002f);

    if(m_pIA) m_pIA->RefreshData(Analog.wDataIA*0.0333333f);
    if(m_pIC) m_pIC->RefreshData(Analog.wDataIC*0.0333333f);

    if(m_pIB) m_pIB->RefreshData(Analog.wDataIB*0.0333333f);
    if(m_pUa) m_pUa->RefreshData(Analog.wDataUa*0.04f);
    if(m_pUb) m_pUb->RefreshData(Analog.wDataUb*0.04f);
    if(m_pUc) m_pUc->RefreshData(Analog.wDataUc*0.04f);
    if(m_pUab) m_pUab->RefreshData(Analog.wDataUab*0.04f);
    if(m_pUbc) m_pUbc->RefreshData(Analog.wDataUbc*0.04f);
    if(m_pUca) m_pUca->RefreshData(Analog.wDataUca*0.04f);

    if(m_p3I0) m_p3I0->RefreshData(Analog.wData3I0*0.0333333f);
    if(m_pF) m_pF->RefreshData(Analog.wDataF*0.01f);
    if(m_pP) m_pP->RefreshData(Analog.nDataP*0.72f);
    if(m_pQ) m_pQ->RefreshData(Analog.nDataQ*0.72f);
    if(m_pPF) m_pPF->RefreshData(Analog.nDataPF*0.001f);
}

void CMyUnitNPS7510::OnEditDeviceParam(CMyDataNPSParam* pDataParam)
{
    CMyDlgParam dlg;
    dlg.m_pDataParam = pDataParam;
    dlg.m_wndGrid.m_ParamR = pDataParam->m_deviceParamR;
    dlg.m_wndGrid.m_ParamW = pDataParam->m_deviceParamR;
    MyDoModal(&dlg, NPS7510DLL.hModule);
}

void CMyUnitNPS7510::OnEditRegulate(CMyDataNPSRegulate* pDataRegulate)
{
    CMyDlgRegulate dlg;
    dlg.m_pDataRegulte = pDataRegulate;
    dlg.m_wndGrid.m_RegulateR = pDataRegulate->m_RegulateR;
    dlg.m_wndGrid.m_RegulateW = pDataRegulate->m_RegulateR;
    MyDoModal(&dlg, NPS7510DLL.hModule);
}

void CMyUnitNPS7510::OnEditSetpoint(CMyDataNPSSetpoint* pDataSetpoint)
{
    CMyDlgSetpoint dlg;
    dlg.m_pDataSetpoint = pDataSetpoint;
    dlg.m_wndGrid.m_SetpointR = pDataSetpoint->m_SetpointR;
    dlg.m_wndGrid.m_SetpointW = pDataSetpoint->m_SetpointR;
    MyDoModal(&dlg, NPS7510DLL.hModule);
}

void CMyUnitNPS7510::OnExcuteYC(CMyDataNPSYC* pDataYC)
{
    CMyDlgYC dlg;
    dlg.m_pDataYC = pDataYC;
    MyDoModal(&dlg, NPS7510DLL.hModule);
}

void CMyUnitNPS7510::ReceiveEventTable(COMCONTROL* pCC)
{
    WORD wCount = m_wCountEvent - m_wCountEventOld;
    if(wCount>20)
    {
        m_wCountEventOld = m_wCountEvent;
        return;
    }
    for(int i=0;i<wCount;++i)
    {
        WORD wAddrOffSet = (m_wCountEventOld%EVENT_COUNT)*sizeof(EVENT)/sizeof(short);
        if(MODBUS_Read(pCC,LOGADDR_EVENTTABLE+wAddrOffSet,sizeof(EVENT)/sizeof(short))==FALSE) return;
        EVENT Event;
        memcpy(&Event, pCCRX+3,sizeof(Event));
        EVTMSG EventMsg;
        EventMsg.wYear = Event.time.wYear + 2000;
        EventMsg.Mon = Event.time.wMonth;
        EventMsg.Day = Event.time.wDay;
        EventMsg.Hour = Event.time.wHour;
        EventMsg.Min = Event.time.wMinute;
        EventMsg.Sec = Event.time.wSecond;
        EventMsg.wMs = Event.time.wMilliSecond;
        EventMsg.strContent = GetEventText(Event);
        EventMsg.clrColor = RGB(255,0,0);
        g_MngEvent.SndMsg(EventMsg);
        m_wCountEventOld++;
    }
}

const char* g_pszInName[SWITCH_COUNT] =
{
    "闭锁重合闸/重瓦斯",
    "弹簧未储能",
    "遥信1/轻瓦斯",
    "遥信2/温高跳闸",
    "遥信3/温高告警",
    "小车工作位置",
    "小车试验位置",
    "接地刀闸合位",
    "远方/就地",
    "HWJ",
    "TWJ",
    "KKJ",
};

enum PROTRCTCODE
{
    PROTECT_DL1 = 0,            // 电流I段;         0
    PROTECT_DL2,                // 电流II段         1
    PROTECT_DL3,                // 电流III段;       2
    PROTECT_LX1,                // 零序I段;         3
    PROTECT_LX2,                // 零序II段;        4
    PROTECT_GFH,                // 过负荷;          5
    PROTECT_DDY,                // 低电压;          6
    PROTECT_CHZ,                // 重合闸;          7
    PROTECT_HJS,                // 后加速;          8
    PROTECT_MAX1
};

enum PROTECTCODE
{
    PROTECT_IN1 = PROTECT_MAX1,
    PROTECT_IN2,
    PROTECT_IN3,
    PROTECT_IN4,
    PROTECT_IN5,
    PROTECT_IN6,
    PROTECT_IN7,
    PROTECT_IN8,
    PROTECT_MAX
};

enum
{
    PROTECTACT_NULL = 0,
    PROTECTACT_IP,
    PROTECTACT_3I0,
    PROTECTACT_U,
};

typedef struct
{
    const char* pszName;
    WORD wAct;
}PROTECTACTINFO;

const PROTECTACTINFO c_protectActInfo[PROTECT_MAX1] = 
{
    {"电流Ⅰ段",	PROTECTACT_IP},
    {"电流Ⅱ段",	PROTECTACT_IP},
    {"电流Ⅲ段",	PROTECTACT_IP},
    {"零流Ⅰ段",	PROTECTACT_3I0},
    {"零流Ⅱ段",	PROTECTACT_3I0},
    {"过负荷",		PROTECTACT_IP},
    {"低电压",		PROTECTACT_U},
    {"重合闸",	    PROTECTACT_NULL},
    {"后加速",	    PROTECTACT_IP},
    //     {NULL,			    NULL,		            0},
};

const char* g_pszINSETName[] =
{
    "重瓦斯",
    "轻瓦斯",
    "温高跳闸",
    "温高告警",
};

CString CMyUnitNPS7510::GetEventText(EVENT& Event)
{
    CString strEventText = "";
    if(Event.wCode>=EVENTCODE_SWITCH && Event.wCode<EVENTCODE_SWITCH+SWITCH_COUNT)
    {
        WORD wIndex = Event.wCode - EVENTCODE_SWITCH;
        strEventText += g_pszInName[wIndex];
        strEventText += "->";
        strEventText += (Event.wData==0)?"分位":"合位";
    }
    if(Event.wCode>=EVENTCODE_PROTECT && Event.wCode<EVENTCODE_PROTECT+256)
    {
        WORD wProtectIndexExt = (WORD)(Event.wCode-EVENTCODE_PROTECT);
        WORD wProtectIndex = wProtectIndexExt&0x001f;
        if(c_protectActInfo[wProtectIndex].pszName)
        {
            strEventText += c_protectActInfo[wProtectIndex].pszName;
            strEventText += "保护动作";
            if(Event.wData!=0xffff)
            {
                strEventText +=  GetEventTextProtect(c_protectActInfo[wProtectIndex].wAct, wProtectIndexExt, Event.wData);
            }
        }
    }
    if(Event.wCode>=EVENTCODE_PROTECT+PROTECT_IN1 && Event.wCode<EVENTCODE_PROTECT+PROTECT_MAX)
    {
        WORD wProtectIndexExt = Event.wCode-EVENTCODE_PROTECT-PROTECT_IN1;
        strEventText += ((char*)g_pszINSETName[wProtectIndexExt]);
        strEventText += ("保护动作");
    }
    switch(Event.wCode)
    {
    case EVENTCODE_ALARMPT3: strEventText = "三相PT断线" + (Event.wData==0)?"":"恢复";
    case EVENTCODE_ALARMPT2: strEventText = "两相PT断线" + (Event.wData==0)?"":"恢复";
    case EVENTCODE_ALARMPT1: strEventText = "单相PT断线" + (Event.wData==0)?"":"恢复";
    case EVENTCODE_ALARMKM: strEventText = "控制回路断线" + (Event.wData==0)?"":"恢复";
    }
    return strEventText;
}

CString CMyUnitNPS7510::GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData)
{
    CString strText = "";
    switch(wProtectAct)
    {
    case PROTECTACT_IP: strText.Format(",I=%.2fA", wActData*0.0333333f); break;
    case PROTECTACT_3I0: strText.Format(",3I0=%.2fA", wActData*0.0333333f); break;
    case PROTECTACT_U: strText.Format(",U=%.2fV", wActData*0.04f); break;
    }
    return strText;


//     if(m_pIa) m_pIa->RefreshData(Analog.wDataIa*0.002f);             // Analog.wDataIa*6.0000
//     if(m_pIb) m_pIb->RefreshData(Analog.wDataIb*0.002f);
//     if(m_pIc) m_pIc->RefreshData(Analog.wDataIc*0.002f);
//     
//     if(m_pIA) m_pIA->RefreshData(Analog.wDataIA*0.0333333f);
//     if(m_pIC) m_pIC->RefreshData(Analog.wDataIC*0.0333333f);
//     
//     if(m_pIB) m_pIB->RefreshData(Analog.wDataIB*0.0333333f);
//     if(m_pUa) m_pUa->RefreshData(Analog.wDataUa*0.04f);
//     if(m_pUb) m_pUb->RefreshData(Analog.wDataUb*0.04f);
//     if(m_pUc) m_pUc->RefreshData(Analog.wDataUc*0.04f);
//     if(m_pUab) m_pUab->RefreshData(Analog.wDataUab*0.04f);
//     if(m_pUbc) m_pUbc->RefreshData(Analog.wDataUbc*0.04f);
//     if(m_pUca) m_pUca->RefreshData(Analog.wDataUca*0.04f);
//     
//     if(m_p3I0) m_p3I0->RefreshData(Analog.wData3I0*0.0333333f);
//     if(m_pF) m_pF->RefreshData(Analog.wDataF*0.01f);
//     if(m_pP) m_pP->RefreshData(Analog.nDataP*0.72f);
//     if(m_pQ) m_pQ->RefreshData(Analog.nDataQ*0.72f);
//     if(m_pPF) m_pPF->RefreshData(Analog.nDataPF*0.001f);
}

void CMyUnitNPS7510::ReceiveWaveRecordHeadList(COMCONTROL* pCC)
{
    int nHeadLen = 10;
    int nWaveLen = sizeof(WAVERECORD)/2;
    int nWaveNo = (m_wCountWaveRecord+1)%WAVERECORD_WAVENUM;
    WAVERECORD WaveRecord;
    CArray<OPList,OPList> arList;
    OPList List;
    for(int i=0;i<WAVERECORD_WAVENUM;i++,nWaveNo = (nWaveNo+1)%WAVERECORD_WAVENUM)
    {
        if(MODBUS_Read(pCC,LOGADDR_WAVERECORD+nWaveNo*nWaveLen,nHeadLen)==FALSE) return;
        memcpy(&WaveRecord,pCCRX+3,nHeadLen*sizeof(WORD));
        if(WaveRecord.wRecordStatus==0xffff && WaveRecord.wFreezeDotNo<WAVERECORD_DOTNUM)
        {
            WORD wYear = WaveRecord.timeFreeze.wYear+2000;
            WORD wMonth = WaveRecord.timeFreeze.wMonth;
            WORD wDay = WaveRecord.timeFreeze.wDay;
            WORD wHour = WaveRecord.timeFreeze.wHour;
            WORD wMinute = WaveRecord.timeFreeze.wMinute;
            WORD wSecond = WaveRecord.timeFreeze.wSecond;
            WORD wMilliSecond = WaveRecord.timeFreeze.wMilliSecond;
            List.strName.Format("Wave:%d-%02d-%02d %02d:%02d:%02d.%03d",
                wYear,wMonth,wDay,wHour,wMinute,wSecond,wMilliSecond);
            List.nIndex = nWaveNo;
            arList.Add(List);
        }
    }
    ASSERT(m_pWaveRecordList);
    m_pWaveRecordList->RefreshData(arList);
    m_bWaveRecordListOK = TRUE;
}

void CMyUnitNPS7510::OnOpenList(CMyDataOPList* pOPList)
{
    CMyOpenList dlg;
//     dlg.m_pUnit = this;
    dlg.m_pOPList = pOPList;
    MyDoModal(&dlg,NPS7510DLL.hModule);
}

void CMyUnitNPS7510::TimeSyn(COMCONTROL* pCC)
{
    CTime timeNow = CTime::GetCurrentTime();
    if(timeNow.GetYear()<2000) return;
    WORD wTime[7];
    wTime[0] = WORD(timeNow.GetYear()-2000);
    wTime[1] = WORD(timeNow.GetMonth());
    wTime[2] = WORD(timeNow.GetDay());
    wTime[3] = WORD(timeNow.GetHour());
    wTime[4] = WORD(timeNow.GetMinute());
    wTime[5] = WORD(timeNow.GetSecond());
    wTime[6] = 0;
    DWORD dwAddressDest = m_nAddr;
    m_nAddr = 0;
    MODBUS_Write(pCC,LOGADDR_DEVICETIME,7,wTime);
    m_nAddr = dwAddressDest;
    m_bTimeSyn = TRUE;
}

BOOL CMyUnitNPS7510::ReceiveWave(COMCONTROL* pCC, int nWaveNo)
{
    WAVERECORD WaveRecord;
    nWaveNo %= WAVERECORD_WAVENUM;
    if(!ReceiveWaveRecordHead(pCC, nWaveNo, WaveRecord)) return FALSE;
    if(!ReceiveWaveRecordData(pCC, nWaveNo, WaveRecord)) return FALSE;
    SaveWave(WaveRecord);
    CString strMessage;
    strMessage.Format("接收故障录波结束,录波号:%d", nWaveNo);
    AddEvent(strMessage);
    return TRUE;
}

BOOL CMyUnitNPS7510::ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORD& Waverecord)
{
    ASSERT(nWaveNo>=0 && nWaveNo<WAVERECORD_WAVENUM);
    int nHeadLen = 10;
    int nWaveLen = sizeof(WAVERECORD)/2;

    if(MODBUS_Read(pCC,LOGADDR_WAVERECORD+nWaveNo*nWaveLen,nHeadLen)==FALSE) return FALSE;
    memcpy(&Waverecord, pCCRX+3, nHeadLen*sizeof(WORD));
    if(Waverecord.wRecordStatus==0xffff && Waverecord.wFreezeDotNo<WAVERECORD_DOTNUM)
    {
        CString strMessage;
        strMessage.Format("接收故障录波开始,录波号:%d",nWaveNo);
        AddEvent(strMessage);
        return TRUE;
    }
    return FALSE;
}

BOOL CMyUnitNPS7510::ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORD& Waverecord)
{
    ASSERT(nWaveNo>=0 && nWaveNo<WAVERECORD_WAVENUM);
    int nHeadLen = 10;
    int nWaveLen = sizeof(WAVERECORD)/2;
    int nDataLen = nWaveLen - nHeadLen;
    int nDataRcv = 0;                     // 已读的时候数据
    while(nDataRcv<nDataLen)
    {
        int nData = nDataLen - nDataRcv;
        if(nData>100) nData = 100;
        if(MODBUS_Read(pCC, LOGADDR_WAVERECORD+nWaveNo*nWaveLen +nHeadLen+nDataRcv, nData)==FALSE) return FALSE;
        memcpy(((BYTE*)Waverecord.wData)+nDataRcv*sizeof(WORD),pCCRX+3,nData*2);
//         if(nData<=125)
//         {
//             memcpy(((BYTE*)Waverecord.wData)+nDataRcv*sizeof(WORD),pCCRX+3,nData*2);
//         }
//         else
//         {
//             memcpy(((BYTE*)Waverecord.wData)+nDataRcv*sizeof(WORD),pCCRX+4,nData*2);
//         }
        nDataRcv += nData;
    }
    return TRUE;
}

void CMyUnitNPS7510::SaveWave(WAVERECORD& Waverecord)
{
    WORD wYear = Waverecord.timeFreeze.wYear+2000;
    WORD wMonth = Waverecord.timeFreeze.wMonth;
    WORD wDay = Waverecord.timeFreeze.wDay;
    WORD wHour = Waverecord.timeFreeze.wHour;
    WORD wMinute = Waverecord.timeFreeze.wMinute;
    WORD wSecond = Waverecord.timeFreeze.wSecond;
    WORD wMilliSecond = Waverecord.timeFreeze.wMilliSecond;
    if(wYear<2000 || wYear>2050) return;
    if(wMonth<1 || wMonth>12) return;
    if(wDay<1 || wDay>31) return;
    if(wHour>23) return;
    if(wMinute>59) return;
    if(wSecond>59) return;
    if(wMilliSecond>999) return;

    CString strFileName;
    strFileName.Format("Wave%d%02d%02d_%02d%02d%02d%03d.www",
                wYear,wMonth,wDay,wHour,wMinute,wSecond,wMilliSecond);

    int nWaveRecordedDot = WAVERECORD_DOTNUM;
    if(Waverecord.wCycleFlag==0) nWaveRecordedDot = min(Waverecord.wFreezeDotNo, WAVERECORD_DOTNUM);
    if(nWaveRecordedDot<24*5) return;
    int nWaveStartDotNo = (Waverecord.wFreezeDotNo+WAVERECORD_DOTNUM-nWaveRecordedDot)%WAVERECORD_DOTNUM;

    CTime time = CTime(wYear,wMonth,wDay,wHour,wMinute,wSecond);
    time -= 10L;                // -10s
    DWORD dwMilliSecond = 10000L + wMilliSecond;
//    dwMilliSecond -= (nWaveRecordedDot-24*5)*(20)/(24);            // 冻结前(nWaveRecordedDot-24*5)点
    dwMilliSecond -= nWaveRecordedDot*(20)/(24);                        // 冻结前(nWaveRecordedDot)点
    time += dwMilliSecond/1000;
    wMilliSecond = (WORD)(dwMilliSecond%1000);

    CMyWaveInfo waveinfo;
    waveinfo.Create(7, 12, nWaveRecordedDot, 24*50);
//     waveinfo.Create(7, 1, nWaveRecordedDot, 24*50);
    waveinfo.SetTime(time.GetTime(),wMilliSecond);

    for(int i=0;i<7;++i)
    {
        float fFullScale;
        float fFullScaleAD;
        float fReg;
        CString strChannelName;
        GetWaveRecordMetrics(i,strChannelName,fFullScale,fFullScaleAD,fReg);
        ASSERT(strChannelName.IsEmpty()==FALSE);
        SetWaveInfoAD(waveinfo,i,strChannelName,fFullScale,fFullScaleAD, nWaveRecordedDot, nWaveStartDotNo, Waverecord, fReg);
    }
// =========for debug
//     float fData[7][240];
//     for(i=0;i<7;++i)
//     {
//         float* pfData = waveinfo.m_pDataAD + i*nWaveRecordedDot;
//         for(int j=0;j<240;++j)
//         {
//             fData[i][j] = pfData[j];
//         }
//     }

    for(i=0;i<12;i++) SetWaveInfoDI(waveinfo, i, 1<<i, nWaveRecordedDot, nWaveStartDotNo, Waverecord);
//     SetWaveInfoDI(waveinfo, 0, (WORD)1<<9, nWaveRecordedDot, nWaveStartDotNo, Waverecord);

    waveinfo.StoreToFile(m_strName, strFileName);
}

void CMyUnitNPS7510::GetWaveRecordMetrics(int nIndex,CString& strChannelName,float& fFullScale,float& fFullScaleAD, float& fReg)
{
    strChannelName.Empty();
    REGULATE* pReg = NULL;
    switch(nIndex)
    {
    case 0: strChannelName = "IA:A相保护电流\tA"; fFullScale = 1.414f*100.0f;  fFullScaleAD = 500.f; pReg = &m_pRegulate->m_RegulateR.regulate[3]; break;
    case 1: strChannelName = "IB:B相保护电流\tA"; fFullScale = 1.414f*100.0f;  fFullScaleAD = 500.f; pReg = &m_pRegulate->m_RegulateR.regulate[4]; break;
    case 2: strChannelName = "IC:C相保护电流\tA"; fFullScale = 1.414f*100.0f;  fFullScaleAD = 500.f; pReg = &m_pRegulate->m_RegulateR.regulate[5]; break;
    case 3: strChannelName = "Ua:A相电压\tV"; fFullScale = 1.414f*120.0f; fFullScaleAD = 500.f; pReg = &m_pRegulate->m_RegulateR.regulate[7]; break;
    case 4: strChannelName = "Ub:B相电压\tV"; fFullScale = 1.414f*120.0f; fFullScaleAD = 500.f; pReg = &m_pRegulate->m_RegulateR.regulate[8]; break;
    case 5: strChannelName = "Uc:C相电压\tV"; fFullScale = 1.414f*120.0f; fFullScaleAD = 500.f; pReg = &m_pRegulate->m_RegulateR.regulate[9]; break;
    case 6: strChannelName = "3I0:零序电流\tA"; fFullScale = 1.414f*100.0f; fFullScaleAD = 500.f; pReg = &m_pRegulate->m_RegulateR.regulate[6]; break;
    }
    if(pReg)
    {
        float fR = (float)pReg->nRegulateR*0.0001f;
        float fX = (float)pReg->nRegulateX*0.0001f;
        fReg = sqrt(fR*fR+fX*fX);
    }
    else fReg = 1.0f;
}

WORD CMyUnitNPS7510::GetWaveAIData(short nChIndex, WORD* pwData)
{
    // 从g_waveRecord.m_wWaveData[1]开始
    // ((WAVERECORDCHANNELBI+15)&0xfff0):开关量占得字节数;
//     stWaveRecordInfo waveRecordinfo;
//     GetWaveRecordInfo(waveRecordinfo);
    
    short nBits = 10;
    ASSERT(nBits<=16);
    short nBIBits = 16;
    
    WORD wBitIndex = nChIndex*nBits + ((nBIBits+15)&0xfff0);
    WORD wIndexW = (wBitIndex>>4);          // 第几个字
    WORD wIndexB = (wBitIndex&0x0f);        // 字中第几位
    ASSERT(wIndexW<6);
    
    WORD wData1 = pwData[wIndexW];
    WORD wData2 = 0;
    if(wIndexW+1<6) wData2 = pwData[wIndexW+1];
    
    DWORD dwData = (DWORD)wData1 | ((DWORD)wData2<<16);
    dwData = dwData>>wIndexB;
    WORD wMask = (1<<nBits) - 1;
    return (WORD)dwData&wMask;
}

void CMyUnitNPS7510::SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName,float fFullScale,float fFullScaleAD,
                                   int nWaveRecordedDot, int nWaveStartDotNo, WAVERECORD& Waverecord, float fReg)
{
    CString strUnitage = MyReverseSpanExcluding(strChannelName,"\t");
    strChannelName = strChannelName.SpanExcluding("\t");
    waveinfo.SetChannelInfoAD(nChannelNo,strChannelName,strUnitage,fFullScale);
    float fSum = 0;
    float* pData = waveinfo.m_pDataAD + nWaveRecordedDot*nChannelNo;
    for(int i=0;i<nWaveRecordedDot;i++)
    {
        int nDotNo = (nWaveStartDotNo+i)%WAVERECORD_DOTNUM;
        WORD* pWaveData = &(Waverecord.wData[nDotNo][0]);
        int nData;
//         switch(nChannelNo)
//         {
//         case 0: nData = (pWaveData[1]&0x03ff); break;
//         case 1: nData = ((pWaveData[1]&0xfc00)>>10)+((pWaveData[2]&0x000f)<<6); break;
//         case 2: nData = ((pWaveData[2]&0x3ff0)>>4); break;
//         case 3: nData = ((pWaveData[2]&0xc000)>>14)+((pWaveData[3]&0x00ff)<<2); break;
//         case 4: nData = ((pWaveData[3]&0xff00)>>8)+((pWaveData[4]&0x0003)<<8); break;
//         case 5: nData = ((pWaveData[4]&0x0ffc)>>2); break;
//         case 6: nData = ((pWaveData[4]&0xf000)>>12)+((pWaveData[5]&0x003f)<<4); break;
//         case 7: nData = ((pWaveData[5]&0xffc0)>>6); break;
        //         }
        nData = GetWaveAIData(nChannelNo, pWaveData);
//         nData -= 500;
//         float fWaveData = nData*fFullScale/fFullScaleAD;
        pData[i] = (float)nData;
        fSum += (float)nData;
    }
    if(nWaveRecordedDot) fSum /= nWaveRecordedDot;
    for(i=0;i<nWaveRecordedDot;i++)
    {
        float fWaveData = pData[i] - fSum;
        fWaveData = fWaveData*fFullScale/fFullScaleAD;
        fWaveData *= fReg;
        pData[i] = fWaveData;
    }
}

void CMyUnitNPS7510::SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, int nWaveStartDotNo, WAVERECORD& Waverecord)
{
    ASSERT(nChannelNo>=0 && nChannelNo<12);

    CString strChannelName = g_pszInName[nChannelNo];
    waveinfo.SetChannelInfoDI(nChannelNo,strChannelName,"0","1");
    for(int i=0;i<nWaveRecordedDot;i++)
    {
        int nDotNo = (nWaveStartDotNo+i)%WAVERECORD_DOTNUM;
        WORD* pWaveData = &(Waverecord.wData[nDotNo][0]);
        BYTE* pDataDI = waveinfo.m_pDataDI + nChannelNo*nWaveRecordedDot;
        pDataDI[i] = ((pWaveData[0]&wMask)==wMask);
    }
}


