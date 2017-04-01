// PM310.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "CMyUnitModbus.h"
#include "PM310.h"
#include "CMyGridCtrl.h"
#include "CMyDlgParam.h"
#include "CMyDlgRegulate.h"
#include "CMyDlgSetpoint.h"
#include "CMyDlgOpList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*static*/ AFX_EXTENSION_MODULE PM310DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("PM310.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(PM310DLL, hInstance))
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

		new CDynLinkLibrary(PM310DLL);
        CMyUnit::RegisterClass(_T("PM310"), RUNTIME_CLASS(CMyUnitPM310));
        CMyData::RegisterClass(_T("PMParam"), RUNTIME_CLASS(CMyDataPMParam), TRUE);
        CMyData::RegisterClass(_T("PMRegulate"), RUNTIME_CLASS(CMyDataPMRegulate), TRUE);
        CMyData::RegisterClass(_T("PMSetpoint"), RUNTIME_CLASS(CMyDataPMSetpoint), TRUE);
        CMyData::RegisterClass(_T("PMSetpoint"), RUNTIME_CLASS(CMyDataPMSetpoint), TRUE);
        CMyData::RegisterClass(_T("PMOPList"), RUNTIME_CLASS(CMyDataPMOPList), TRUE);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("PM310.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(PM310DLL);
	}
	return 1;   // ok
}

//---------------------------------------------- CMyDataPMParam -----------
IMPLEMENT_SERIAL(CMyDataPMParam,CMyDataOperate,0)

CMyDataPMParam::CMyDataPMParam():CMyDataOperate()
{
    m_bOK = FALSE;
    memset(&m_deviceParamR,0,sizeof(m_deviceParamR));
    memset(&m_deviceParamW,0,sizeof(m_deviceParamW));
}

void CMyDataPMParam::RefreshData(tDEVICEPARAM& DeviceParam)
{
    m_deviceParamR = DeviceParam;
    m_bOK = TRUE;
    IncrementUpdateID();
}

void CMyDataPMParam::StoreToDevice(tDEVICEPARAM& DeviceParam)
{
    m_deviceParamW = DeviceParam;
    m_OperateCode = 0xff;
    IncrementUpdateID();
}

BOOL CMyDataPMParam::ExeOperate(void)
{
    if(m_bOK)
    {
        ASSERT(m_pParentUnit);
        ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitPM310)));
        ((CMyUnitPM310*)m_pParentUnit)->OnEditDeviceParam(this);
    }
    return FALSE;
}

//---------------------------------------------- CMyDataPMRegulate -----------
IMPLEMENT_SERIAL(CMyDataPMRegulate,CMyDataOperate,0)

CMyDataPMRegulate::CMyDataPMRegulate():CMyDataOperate()
{
    m_bOK = FALSE;
    memset(&m_RegulateR,0,sizeof(m_RegulateR));
    memset(&m_RegulateW,0,sizeof(m_RegulateW));
}

void CMyDataPMRegulate::RefreshData(tREGULATESET& Regulate)
{
    m_RegulateR = Regulate;
    m_bOK = TRUE;
    IncrementUpdateID();
}

void CMyDataPMRegulate::StoreToDevice(tREGULATESET& Regulate)
{
    m_RegulateW = Regulate;
    m_OperateCode = 0xff;
    IncrementUpdateID();
}

BOOL CMyDataPMRegulate::ExeOperate(void)
{
    if(m_bOK)
    {
        ASSERT(m_pParentUnit);
        ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitPM310)));
        ((CMyUnitPM310*)m_pParentUnit)->OnEditRegulate(this);
    }
    return FALSE;
}

//---------------------------------------------- CMyDataPMSetpoint -----------
IMPLEMENT_SERIAL(CMyDataPMSetpoint,CMyDataOperate,0)

CMyDataPMSetpoint::CMyDataPMSetpoint():CMyDataOperate()
{
    m_bOK = FALSE;
    memset(&m_SetpointR,0,sizeof(m_SetpointR));
    memset(&m_SetpointW,0,sizeof(m_SetpointW));
}

void CMyDataPMSetpoint::RefreshData(tDEVICESETPOINT& Setpoint)
{
    m_SetpointR = Setpoint;
    m_bOK = TRUE;
    IncrementUpdateID();
}

void CMyDataPMSetpoint::StoreToDevice(tDEVICESETPOINT& Setpoint)
{
    m_SetpointW = Setpoint;
    m_OperateCode = 0xff;
    IncrementUpdateID();
}

BOOL CMyDataPMSetpoint::ExeOperate(void)
{
    if(m_bOK)
    {
        ASSERT(m_pParentUnit);
        ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitPM310)));
        ((CMyUnitPM310*)m_pParentUnit)->OnEditSetpoint(this);
    }
    return FALSE;
}


//------------------------------- CMyDataPMOPList -----------------------------------
IMPLEMENT_SERIAL(CMyDataPMOPList,CMyDataOperate,0)

CMyDataPMOPList::CMyDataPMOPList():CMyDataOperate()
{
    m_nOPIndex = 0;
}

void CMyDataPMOPList::RefreshData(CMyOpListArray& arOpList)
{
    int nSize = arOpList.GetSize();
    m_arOPList.RemoveAll();
    for(int i=0;i<nSize;i++)
    {
        m_arOPList.Add(arOpList[i]);
    }
    IncrementUpdateID();
}

void CMyDataPMOPList::SndCmd(int nOPIndex,BYTE Cmd/*=0xff*/)
{
    m_nOPIndex = nOPIndex;
    m_OperateCode = Cmd;
    IncrementUpdateID();
}

BOOL CMyDataPMOPList::ExeOperate(void)
{
    ASSERT(m_pParentUnit);
    ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitPM310)));
    ((CMyUnitPM310*)m_pParentUnit)->OnOpenList(this);
    return FALSE;
}


//------------------------------------------------------------------------------------------------------------
#define LOGADDR_DEVICETIME		0x0000		// RW;
#define LOGADDR_DEVICEINFO		0x0007		// R;
#define LOGADDR_ANALOGDATA		0x0100		// R;
#define LOGADDR_ANALOGDATAEXT	0x0200		// R;
#define LOGADDR_ANALOGWAVE		0x0300		// R;
#define LOGADDR_DFTDATASET		0x0900		// R;
#define LOGADDR_CONTROLOUT		0x0a00		// RW;
#define LOGADDR_DEVICEPARAM		0x0b00		// RW;
#define LOGADDR_DEVICEINPARAM	0x0c00		// RW;
#define LOGADDR_DEVICEDCPARAM	0x1100		// RW;
#define LOGADDR_DEVICEREGULATE	0x1300		// RW;
#define LOGADDR_DEVICESETPOINT	0x1400		// RW;
#define LOGADDR_DEVICEDRW		0x1600		// RW;
#define LOGADDR_DEVICELAD		0x1800		// RW;
#define LOGADDR_EVENTTABLE		0x1a00		// R;
#define LOGADDR_WAVERECORD		0x2000		// R

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
    WORD wCRC;
}tDEVICEINFO;

typedef struct
{
    WORD wDataIa;
    WORD wDataIb;
    WORD wDataIc;
    WORD wDataUa;
    WORD wDataUb;
    WORD wDataUc;
    WORD wDataUab;
    WORD wDataUbc;
    WORD wDataUca;
    //    WORD wData3I0;
    WORD wDataF;
    short nDataP;
    short nDataQ;
    short nDataS;
    short nDataPF;
    short nAngIa;
    short nAngIb;
    short nAngIc;
    short nAngUa;
    short nAngUb;
    short nAngUc;
    short nAngUab;
    short nAngUbc;
    short nAngUca;
}tANALOGDATA;

typedef struct
{
    DWORD dwDataPhImp;
    DWORD dwDataQhImp;
    DWORD dwDataPhExp;
    DWORD dwDataQhExp;
}tANALOGDATAEXT;

//---------------------------------------------- CMyUnitPM310 -----------------------
IMPLEMENT_SERIAL(CMyUnitPM310,CMyUnitModbus,0)

CMyUnitPM310::CMyUnitPM310():CMyUnitModbus(),
        m_fScaleI(6), m_fScaleUll(260)
{
    m_bInfoOK = FALSE;
    m_bTimeSyn = FALSE;
    m_bParamOK = FALSE;
    m_bRegulateOK = FALSE;
    m_bSetpointOK = FALSE;
    m_bWaveRecordListOK = FALSE;

    m_wCountParam = 0;
    m_wCountParamOld = 0;
    m_wCountRegulate = 0;
    m_wCountRegulateOld = 0;
    m_wCountSetpoint = 0;
    m_wCountSetpointOld = 0;
    m_wCountWaveRecord = 0;
    m_wCountWaveRecordOld = 0;
}

CMyUnitPM310::~CMyUnitPM310()
{
}

BOOL CMyUnitPM310::OnCreate(void)
{
    CMyUnitModbus::OnCreate();

//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ia"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngIa"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ib"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngIb"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ic"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngIc"));
// 
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ua"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngUa"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ub"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngUb"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Uc"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngUc"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Uab"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngUab"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Ubc"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngUbc"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Uca"));
//     AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("AngUca"));

    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Ia"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Ib"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Ic"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Ua"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Ub"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Uc"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Uab"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Ubc"));
    AddDataFactory(RUNTIME_CLASS(CMyDataVector), _T("Uca"));

    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Freq"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("P"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Q"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("S"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("PF"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Epimp"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Eqimp"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Epexp"));
    AddDataFactory(RUNTIME_CLASS(CMyDataFloat), _T("Eqexp"));

    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI01"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI02"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI03"));
    AddDataFactory(RUNTIME_CLASS(CMyDataBin), _T("BI04"));

    AddDataFactory(RUNTIME_CLASS(CMyDataString), _T("CRCInfo"));

    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("InitDevice"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("Reset"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("FreezeWave"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("Adjust"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("TimeSyn"));
    
    AddDataFactory(RUNTIME_CLASS(CMyDataPMParam), _T("Param"));
    AddDataFactory(RUNTIME_CLASS(CMyDataPMRegulate), _T("Regulate"));
    AddDataFactory(RUNTIME_CLASS(CMyDataPMSetpoint), _T("Setpoint"));
    AddDataFactory(RUNTIME_CLASS(CMyDataPMOPList), _T("WaveRecordList"));

    return TRUE;
}

BOOL CMyUnitPM310::OnCreateData(CMyData* pData)
{
    CMyUnitModbus::OnCreateData(pData);

//     if(pData->m_strField==_T("Ia")) ((CMyDataFloat*)pData)->Initialize(_T("A相电流"), _T("A"), 0x03);
//     else if(pData->m_strField==_T("Ib")) ((CMyDataFloat*)pData)->Initialize(_T("B相电流"), _T("A"), 0x03);
//     else if(pData->m_strField==_T("Ic")) ((CMyDataFloat*)pData)->Initialize(_T("C相电流"), _T("A"), 0x03);
//     else if(pData->m_strField==_T("AngIa")) ((CMyDataFloat*)pData)->Initialize(_T("A相电流角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("AngIb")) ((CMyDataFloat*)pData)->Initialize(_T("B相电流角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("AngIc")) ((CMyDataFloat*)pData)->Initialize(_T("C相电流角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("Ua")) ((CMyDataFloat*)pData)->Initialize(_T("A相电压"), _T("V"), 0x01);
//     else if(pData->m_strField==_T("Ub")) ((CMyDataFloat*)pData)->Initialize(_T("B相电压"), _T("V"), 0x01);
//     else if(pData->m_strField==_T("Uc")) ((CMyDataFloat*)pData)->Initialize(_T("C相电压"), _T("V"), 0x01);
//     else if(pData->m_strField==_T("Uab")) ((CMyDataFloat*)pData)->Initialize(_T("AB线电压"), _T("V"), 0x01);
//     else if(pData->m_strField==_T("Ubc")) ((CMyDataFloat*)pData)->Initialize(_T("BC线电压"), _T("V"), 0x01);
//     else if(pData->m_strField==_T("Uca")) ((CMyDataFloat*)pData)->Initialize(_T("CA线电压"), _T("V"), 0x01);
//     else if(pData->m_strField==_T("AngUa")) ((CMyDataFloat*)pData)->Initialize(_T("A相电压角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("AngUb")) ((CMyDataFloat*)pData)->Initialize(_T("A相电压角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("AngUc")) ((CMyDataFloat*)pData)->Initialize(_T("A相电压角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("AngUab")) ((CMyDataFloat*)pData)->Initialize(_T("A线电压角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("AngUbc")) ((CMyDataFloat*)pData)->Initialize(_T("A线电压角度"), _T("°"), 0x01);
//     else if(pData->m_strField==_T("AngUca")) ((CMyDataFloat*)pData)->Initialize(_T("A线电压角度"), _T("°"), 0x01);

    if(pData->m_strField==_T("Ia")) ((CMyDataVector*)pData)->Initialize(_T("A相电流"), _T("A"), 0x03, 0x01, 1);
    else if(pData->m_strField==_T("Ib")) ((CMyDataVector*)pData)->Initialize(_T("B相电流"), _T("A"), 0x03, 0x01, 1);
    else if(pData->m_strField==_T("Ic")) ((CMyDataVector*)pData)->Initialize(_T("C相电流"), _T("A"), 0x03, 0x01, 1);
    else if(pData->m_strField==_T("Ua")) ((CMyDataVector*)pData)->Initialize(_T("A相电压"), _T("V"), 0x01, 0x01, 1);
    else if(pData->m_strField==_T("Ub")) ((CMyDataVector*)pData)->Initialize(_T("B相电压"), _T("V"), 0x01, 0x01, 1);
    else if(pData->m_strField==_T("Uc")) ((CMyDataVector*)pData)->Initialize(_T("C相电压"), _T("V"), 0x01, 0x01, 1);
    else if(pData->m_strField==_T("Uab")) ((CMyDataVector*)pData)->Initialize(_T("AB线电压"), _T("V"), 0x01, 0x01, 1);
    else if(pData->m_strField==_T("Ubc")) ((CMyDataVector*)pData)->Initialize(_T("BC线电压"), _T("V"), 0x01, 0x01, 1);
    else if(pData->m_strField==_T("Uca")) ((CMyDataVector*)pData)->Initialize(_T("CA线电压"), _T("V"), 0x01, 0x01, 1);

    else if(pData->m_strField==_T("Freq")) ((CMyDataFloat*)pData)->Initialize(_T("频率"), _T("Hz"), 0x02);
    else if(pData->m_strField==_T("P")) ((CMyDataFloat*)pData)->Initialize(_T("有功功率"), _T("W"), 0x0);
    else if(pData->m_strField==_T("Q")) ((CMyDataFloat*)pData)->Initialize(_T("无功功率"), _T("Var"), 0x0);
    else if(pData->m_strField==_T("S")) ((CMyDataFloat*)pData)->Initialize(_T("视在功率"), _T("VA"), 0x0);
    else if(pData->m_strField==_T("PF")) ((CMyDataFloat*)pData)->Initialize(_T("功率因数"), _T(""), 0x03);
    else if(pData->m_strField==_T("Epimp")) ((CMyDataFloat*)pData)->Initialize(_T("正向有功"), _T("kWh"), 0x01);
    else if(pData->m_strField==_T("Eqimp")) ((CMyDataFloat*)pData)->Initialize(_T("正向无功"), _T("kVarh"), 0x01);
    else if(pData->m_strField==_T("Epexp")) ((CMyDataFloat*)pData)->Initialize(_T("反向有功"), _T("kWh"), 0x01);
    else if(pData->m_strField==_T("Eqexp")) ((CMyDataFloat*)pData)->Initialize(_T("反向无功"), _T("kVarh"), 0x01);

    else if(pData->m_strField==_T("BI01")) ((CMyDataBin*)pData)->Initialize(_T("DI1"));
    else if(pData->m_strField==_T("BI02")) ((CMyDataBin*)pData)->Initialize(_T("DI2"));
    else if(pData->m_strField==_T("BI03")) ((CMyDataBin*)pData)->Initialize(_T("DI3"));
    else if(pData->m_strField==_T("BI04")) ((CMyDataBin*)pData)->Initialize(_T("DI4"));
    else if(pData->m_strField==_T("CRCInfo")) ((CMyDataString*)pData)->Initialize(_T("CRC信息"));

    else if(pData->m_strField==_T("InitDevice")) ((CMyDataOperate*)pData)->Initialize(_T("装置初始化"));
    else if(pData->m_strField==_T("Reset")) ((CMyDataOperate*)pData)->Initialize(_T("装置复归"));
    else if(pData->m_strField==_T("FreezeWave")) ((CMyDataOperate*)pData)->Initialize(_T("手动录波"));
    else if(pData->m_strField==_T("Adjust")) ((CMyDataOperate*)pData)->Initialize(_T("校正"));
    else if(pData->m_strField==_T("TimeSyn")) ((CMyDataOperate*)pData)->Initialize(_T("校时"));
    else if(pData->m_strField==_T("Param")) ((CMyDataPMParam*)pData)->Initialize(_T("编辑参数"));
    else if(pData->m_strField==_T("Regulate")) ((CMyDataPMParam*)pData)->Initialize(_T("编辑校正系数"));
    else if(pData->m_strField==_T("Setpoint")) ((CMyDataPMSetpoint*)pData)->Initialize(_T("编辑保护定值"));
    else if(pData->m_strField==_T("WaveRecordList")) ((CMyDataPMOPList*)pData)->Initialize("故障录波列表");

    return TRUE;
}

void CMyUnitPM310::OnPortOpen(void)
{
    CMyUnitModbus::OnPortOpen();

//     m_pIa = (CMyDataFloat*)GetData(_T("Ia"));
//     m_pIb = (CMyDataFloat*)GetData(_T("Ib"));
//     m_pIc = (CMyDataFloat*)GetData(_T("Ic"));
//     m_pAngIa = (CMyDataFloat*)GetData(_T("AngIa"));
//     m_pAngIb = (CMyDataFloat*)GetData(_T("AngIb"));
//     m_pAngIc = (CMyDataFloat*)GetData(_T("AngIc"));
// 
//     m_pUa = (CMyDataFloat*)GetData(_T("Ua"));
//     m_pUb = (CMyDataFloat*)GetData(_T("Ub"));
//     m_pUc = (CMyDataFloat*)GetData(_T("Uc"));
//     m_pUab = (CMyDataFloat*)GetData(_T("Uab"));
//     m_pUbc = (CMyDataFloat*)GetData(_T("Ubc"));
//     m_pUca = (CMyDataFloat*)GetData(_T("Uca"));
//     m_pAngUa = (CMyDataFloat*)GetData(_T("AngUa"));
//     m_pAngUb = (CMyDataFloat*)GetData(_T("AngUb"));
//     m_pAngUc = (CMyDataFloat*)GetData(_T("AngUc"));
//     m_pAngUab = (CMyDataFloat*)GetData(_T("AngUab"));
//     m_pAngUbc = (CMyDataFloat*)GetData(_T("AngUbc"));
//     m_pAngUca = (CMyDataFloat*)GetData(_T("AngUca"));

    m_pIa = (CMyDataVector*)GetData(_T("Ia"));
    m_pIb = (CMyDataVector*)GetData(_T("Ib"));
    m_pIc = (CMyDataVector*)GetData(_T("Ic"));

    m_pUa = (CMyDataVector*)GetData(_T("Ua"));
    m_pUb = (CMyDataVector*)GetData(_T("Ub"));
    m_pUc = (CMyDataVector*)GetData(_T("Uc"));
    m_pUab = (CMyDataVector*)GetData(_T("Uab"));
    m_pUbc = (CMyDataVector*)GetData(_T("Ubc"));
    m_pUca = (CMyDataVector*)GetData(_T("Uca"));

    m_pFreq = (CMyDataFloat*)GetData(_T("Freq"));
    m_pP = (CMyDataFloat*)GetData(_T("P"));
    m_pQ = (CMyDataFloat*)GetData(_T("Q"));
    m_pS = (CMyDataFloat*)GetData(_T("S"));
    m_pPF = (CMyDataFloat*)GetData(_T("PF"));

    m_pEpimp = (CMyDataFloat*)GetData(_T("Epimp"));
    m_pEqimp = (CMyDataFloat*)GetData(_T("Eqimp"));
    m_pEpexp= (CMyDataFloat*)GetData(_T("Epexp"));
    m_pEqexp = (CMyDataFloat*)GetData(_T("Eqexp"));

    m_pBi[0] = (CMyDataBin*)GetData(_T("BI01"));
    m_pBi[1] = (CMyDataBin*)GetData(_T("BI02"));
    m_pBi[2] = (CMyDataBin*)GetData(_T("BI03"));
    m_pBi[3] = (CMyDataBin*)GetData(_T("BI04"));

    m_pCRCInfo = (CMyDataString*)GetData(_T("CRCInfo"));

    m_pOpInitDevice = (CMyDataOperate*)GetData(_T("InitDevice"));
    m_pOpReset = (CMyDataOperate*)GetData(_T("Reset"));
    m_pOpFreezeWave = (CMyDataOperate*)GetData(_T("FreezeWave"));
    m_pOpAdjust = (CMyDataOperate*)GetData(_T("Adjust"));
    m_pOpTimesyn = (CMyDataOperate*)GetData(_T("TimeSyn"));
    m_pParam = (CMyDataPMParam*)GetData(_T("Param"));
    m_pRegulate = (CMyDataPMRegulate*)GetData(_T("Regulate"));
    m_pSetpoint = (CMyDataPMSetpoint*)GetData(_T("Setpoint"));
    m_pWaveRecordList = (CMyDataPMOPList*)GetData("WaveRecordList");
}

void CMyUnitPM310::ExchangeComData(COMCONTROL* pCC)
{
    if(!m_bInfoOK) { ReceiveInfo(pCC); return; }
    if(!m_bTimeSyn) { TimeSyn(pCC); return; }
    if(!m_bParamOK) { ReceiveParam(pCC); return; }
    if(!m_bRegulateOK) { ReceiveRegulate(pCC); return; }
    if(!m_bSetpointOK) { ReceiveSetpoint(pCC); return; }
    if(!m_bWaveRecordListOK) { ReceiveWaveRecordHeadList(pCC); return; }

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
        m_wCountWaveRecordOld = m_wCountWaveRecord;
        return;
    }

    if(m_pParam && m_pParam->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC,LOGADDR_DEVICEPARAM,sizeof(tDEVICEPARAM)/sizeof(short),(WORD*)&(m_pParam->m_deviceParamW));
        m_pParam->EndOperate();
    }

    if(m_pRegulate && m_pRegulate->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC,LOGADDR_DEVICEREGULATE,sizeof(tREGULATESET)/sizeof(short),(WORD*)&(m_pRegulate->m_RegulateW));
        m_pRegulate->EndOperate();
    }

    if(m_pSetpoint && m_pSetpoint->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC,LOGADDR_DEVICESETPOINT,sizeof(tDEVICESETPOINT)/sizeof(short),(WORD*)&(m_pSetpoint->m_SetpointW));
        m_pSetpoint->EndOperate();
    }

    if(m_pOpInitDevice && m_pOpInitDevice->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_INITDEVICE, 0xaaaa);
        m_pOpInitDevice->EndOperate();
    }

    if(m_pOpReset && m_pOpReset->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_RESETDEVICE, 0xaaaa);
        m_pOpReset->EndOperate();
    }

    if(m_pOpFreezeWave && m_pOpFreezeWave->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_FREEZEWAVE, 0xaaaa);
        m_pOpFreezeWave->EndOperate();
    }

    if(m_pOpAdjust && m_pOpAdjust->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_ADJUST, 0xaaaa);
        m_pOpAdjust->EndOperate();
    }

    if(m_pOpTimesyn && m_pOpTimesyn->GetOperateCode()==0xff)
    {
        TimeSyn(pCC);
        m_pOpTimesyn->EndOperate();
    }

    if(m_pWaveRecordList && m_pWaveRecordList->GetOperateCode())
    {
//         int nWaveNo = m_pWaveRecordList->m_arOPList[m_pWaveRecordList->m_nOPIndex].nIndex;
        int nWaveNo = m_pWaveRecordList->m_nOPIndex;
        ReceiveWave(pCC, nWaveNo);
        m_pWaveRecordList->EndOperate();
    }

    m_wTask = ++m_wTask%4;
    switch(m_wTask)
    {
    case 0: ReceiveInfo(pCC); return;
    case 1: ReceiveAnalog(pCC); return;
    case 2: ReceiveAnalogExt(pCC); return;
    case 3: ReceiveEventTable(pCC); return;
    }
}

void CMyUnitPM310::ReceiveInfo(COMCONTROL* pCC)
{
    int i;
    if(MODBUS_Read(pCC, LOGADDR_DEVICEINFO, (sizeof(tDEVICEINFO)/sizeof(WORD)))) return;
    tDEVICEINFO deviceInfo;
    CopyByte2WORDHL((WORD*)&deviceInfo, pCCRX+3, sizeof(tDEVICEINFO)/sizeof(WORD));
    if(deviceInfo.wDeviceType!=310)
    {
        AddEvent(_T("设备类型不匹配!"));
        return;
    }

    WORD wMask = 0x01;
    for(i=0; i<SWITCH_COUNT; i++, wMask = wMask<<1)
    {
        if(m_pBi[i]) m_pBi[i]->RefreshData((deviceInfo.wSwitchStatus1&wMask)?1:0);
    }

    CString strCRC;
    strCRC.Format(_T("0x%4X"), deviceInfo.wCRC);
    if(m_pCRCInfo) m_pCRCInfo->RefreshData(strCRC);

    m_wCountParam = deviceInfo.wCountDeviceParam;
    m_wCountRegulate = deviceInfo.wCountDeviceRegulate;
    m_wCountSetpoint = deviceInfo.wCountDeviceSetpoint;
    m_wCountWaveRecord = deviceInfo.wCountWaveRecord;
    if(m_bInfoOK==FALSE)
    {
        m_wCountParamOld = deviceInfo.wCountDeviceParam;
        m_wCountRegulateOld = deviceInfo.wCountDeviceRegulate;
        m_wCountSetpointOld = deviceInfo.wCountDeviceSetpoint;
        m_wCountWaveRecordOld = deviceInfo.wCountWaveRecord;
    }

    m_bInfoOK = TRUE;
}

void CMyUnitPM310::TimeSyn(COMCONTROL* pCC)
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
    MODBUS_Write(pCC, LOGADDR_DEVICETIME, 7, wTime);
    m_nAddr = dwAddressDest;
    m_bTimeSyn = TRUE;
}

void CMyUnitPM310::ReceiveParam(COMCONTROL* pCC)
{
    int nLen = sizeof(tDEVICEPARAM)/sizeof(WORD);
    if(MODBUS_Read(pCC, LOGADDR_DEVICEPARAM, nLen)) return;
    tDEVICEPARAM deviceParam;
    CopyByte2WORDHL((WORD*)&deviceParam, pCCRX+3, nLen);

    if(m_pParam) m_pParam->RefreshData(deviceParam);
    m_bParamOK = TRUE;
}

void CMyUnitPM310::OnEditDeviceParam(CMyDataPMParam* pDataParam)
{
    CMyDlgParam dlg;
    dlg.m_pDataParam = pDataParam;
    MyDoModal(&dlg, PM310DLL.hModule);
}

void CMyUnitPM310::ReceiveAnalog(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_ANALOGDATA, (sizeof(tANALOGDATA)/sizeof(WORD)))) return;
    tANALOGDATA Analog;
    CopyByte2WORDHL((WORD*)&Analog, pCCRX+3, sizeof(tANALOGDATA)/sizeof(WORD));

//     RefreshFloat(m_pIa, m_fScaleI, Analog.wDataIa);
//     RefreshFloat(m_pIb, m_fScaleI, Analog.wDataIb);
//     RefreshFloat(m_pIc, m_fScaleI, Analog.wDataIc);
//     RefreshFloat(m_pAngIa, (BYTE)0x01, Analog.nAngIa);
//     RefreshFloat(m_pAngIb, (BYTE)0x01, Analog.nAngIb);
//     RefreshFloat(m_pAngIc, (BYTE)0x01, Analog.nAngIc);
// 
//     RefreshFloat(m_pUa, m_fScaleUll, Analog.wDataUa);
//     RefreshFloat(m_pUb, m_fScaleUll, Analog.wDataUb);
//     RefreshFloat(m_pUc, m_fScaleUll, Analog.wDataUc);
//     RefreshFloat(m_pUab, m_fScaleUll, Analog.wDataUab);
//     RefreshFloat(m_pUbc, m_fScaleUll, Analog.wDataUbc);
//     RefreshFloat(m_pUca, m_fScaleUll, Analog.wDataUca);
//     RefreshFloat(m_pAngUa, (BYTE)0x01, Analog.nAngUa);
//     RefreshFloat(m_pAngUb, (BYTE)0x01, Analog.nAngUb);
//     RefreshFloat(m_pAngUc, (BYTE)0x01, Analog.nAngUc);
//     RefreshFloat(m_pAngUab, (BYTE)0x01, Analog.nAngUab);
//     RefreshFloat(m_pAngUbc, (BYTE)0x01, Analog.nAngUbc);
//     RefreshFloat(m_pAngUca, (BYTE)0x01, Analog.nAngUca);
    CMyVector Vec;
    Vec.SetPolar(GetAIFloat(m_fScaleI, Analog.wDataIa), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIa)));
    if(m_pIa) m_pIa->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleI, Analog.wDataIb), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIb)));
    if(m_pIb) m_pIb->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleI, Analog.wDataIc), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIc)));
    if(m_pIc) m_pIc->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUa), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUa)));
    if(m_pUa) m_pUa->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUb), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUb)));
    if(m_pUb) m_pUb->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUc), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUc)));
    if(m_pUc) m_pUc->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUab), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUab)));
    if(m_pUab) m_pUab->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUbc), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUbc)));
    if(m_pUbc) m_pUbc->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUca), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUca)));
    if(m_pUca) m_pUca->RefreshData(Vec);

    float fScaleS = m_fScaleUll*m_fScaleI;
    RefreshFloat(m_pFreq, (BYTE)0x02, Analog.wDataF);
    RefreshFloat(m_pP, fScaleS, Analog.nDataP);
    RefreshFloat(m_pQ, fScaleS, Analog.nDataQ);
    RefreshFloat(m_pS, fScaleS, Analog.nDataS);

    RefreshFloat(m_pPF, (BYTE)0x03, Analog.nDataPF);

}

void CMyUnitPM310::ReceiveAnalogExt(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_ANALOGDATAEXT, (sizeof(tANALOGDATAEXT)/sizeof(WORD)))) return;
    tANALOGDATAEXT AnalogExt;
    CopyByte2WORDHL((WORD*)&AnalogExt, pCCRX+3, sizeof(tANALOGDATAEXT)/sizeof(WORD));

    if(m_pEpimp) m_pEpimp->RefreshData(AnalogExt.dwDataPhImp*0.1f);
    if(m_pEqimp) m_pEqimp->RefreshData(AnalogExt.dwDataQhImp*0.1f);
    if(m_pEpexp) m_pEpexp->RefreshData(AnalogExt.dwDataPhExp*0.1f);
    if(m_pEqexp) m_pEqexp->RefreshData(AnalogExt.dwDataQhExp*0.1f);
}

void CMyUnitPM310::ReceiveRegulate(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_DEVICEREGULATE, (sizeof(tREGULATESET)/sizeof(WORD)))) return;
    tREGULATESET ReuglateSet;
    CopyByte2WORDHL((WORD*)&ReuglateSet, pCCRX+3, sizeof(tREGULATESET)/sizeof(WORD));

    if(m_pRegulate) m_pRegulate->RefreshData(ReuglateSet);

    m_bRegulateOK = TRUE;
}

void CMyUnitPM310::OnEditRegulate(CMyDataPMRegulate* pDataRegulate)
{
    CMyDlgRegulate dlg;
    dlg.m_pDataRegulte = pDataRegulate;
    dlg.m_wndGrid.m_RegulateR = pDataRegulate->m_RegulateR;
    dlg.m_wndGrid.m_RegulateW = pDataRegulate->m_RegulateR;
    MyDoModal(&dlg, PM310DLL.hModule);
}

void CMyUnitPM310::ReceiveSetpoint(COMCONTROL* pCC)
{
    if(MODBUS_Read(pCC, LOGADDR_DEVICESETPOINT, (sizeof(tDEVICESETPOINT)/sizeof(WORD)))) return;
    tDEVICESETPOINT Setpoint;
    CopyByte2WORDHL((WORD*)&Setpoint, pCCRX+3, sizeof(tDEVICESETPOINT)/sizeof(WORD));
    
    if(m_pSetpoint) m_pSetpoint->RefreshData(Setpoint);
    
    m_bSetpointOK = TRUE;
}

void CMyUnitPM310::OnEditSetpoint(CMyDataPMSetpoint* pDataSetpoint)
{
    CMyDlgSetpoint dlg;
    dlg.m_pDataSetpoint = pDataSetpoint;
    dlg.m_wndGrid.m_SetpointR = pDataSetpoint->m_SetpointR;
    dlg.m_wndGrid.m_SetpointW = pDataSetpoint->m_SetpointR;
    MyDoModal(&dlg, PM310DLL.hModule);
}

void CMyUnitPM310::ReceiveEventTable(COMCONTROL* pCC)
{
    while(MODBUS_Read(pCC,LOGADDR_EVENTTABLE,sizeof(EVENT)/sizeof(short))==COMERR_NoErr)
    {
        EVENT Event;
        CopyByte2WORDHL((WORD*)&Event, pCCRX+3,sizeof(Event)/sizeof(short));
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
    }
}

const char* g_pszInName[SWITCH_COUNT] =
{
    "DI1",
    "DI2",
    "DI3",
    "DI4",
};

enum PROTRCTCODE
{
    PROTECT_DL1 = 0,            // 电流I段;         0
    PROTECT_DL2,                // 电流II段         1
    PROTECT_GY1,                // 过压I段;         2
    PROTECT_GY2,                // 过压II段;        3
    PROTECT_QY1,                // 欠压I段;         4
    PROTECT_QY2,                // 欠压II段;        5
    PROTECT_MAX1
};

enum PROTECTCODE
{
    PROTECT_IN1 = PROTECT_MAX1,
    PROTECT_IN2,
    PROTECT_IN3,
    PROTECT_IN4,
    PROTECT_MAX
};

enum
{
    PROTECTACT_NULL = 0,
    PROTECTACT_IP,
    PROTECTACT_U,
    PROTECTACT_3I0,
};

typedef struct
{
    const char* pszName;
    WORD wAct;
}PROTECTACTINFO;

static const PROTECTACTINFO c_protectActInfo[PROTECT_MAX1] = 
{
    {"电流Ⅰ段",	PROTECTACT_IP},
    {"电流Ⅱ段",	PROTECTACT_IP},
    {"过压Ⅰ段",	PROTECTACT_U},
    {"过压Ⅱ段",	PROTECTACT_U},
    {"欠压Ⅰ段",	PROTECTACT_U},
    {"欠压Ⅱ段",	PROTECTACT_U},
    //     {NULL,			    NULL,		            0},
};

static const char* g_pszINSETName[] =
{
    "DI1",
    "DI2",
    "DI3",
    "DI4",
};

static const char* g_pszDoName[] =
{
    "J1",
    "J2",
};

CString CMyUnitPM310::GetEventText(EVENT& Event)
{
    CString strEventText = "";
    if(Event.wCode>=EVENTCODE_REMOTE && Event.wCode<EVENTCODE_REMOTE+2)
    {
        strEventText += g_pszDoName[Event.wCode-EVENTCODE_REMOTE];
        strEventText += _T("->");
        strEventText += _T("遥控出口");
    }
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
//     switch(Event.wCode)
//     {
//     case EVENTCODE_ALARMPT3: strEventText = "三相PT断线" + (Event.wData==0)?"":"恢复";
//     case EVENTCODE_ALARMPT2: strEventText = "两相PT断线" + (Event.wData==0)?"":"恢复";
//     case EVENTCODE_ALARMPT1: strEventText = "单相PT断线" + (Event.wData==0)?"":"恢复";
//     case EVENTCODE_ALARMKM: strEventText = "控制回路断线" + (Event.wData==0)?"":"恢复";
//     }
    return strEventText;
}

CString CMyUnitPM310::GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData)
{
    CString strText = "";
    switch(wProtectAct)
    {
    case PROTECTACT_IP: strText.Format(",I=%.2fA", wActData*0.0333333f); break;
    case PROTECTACT_3I0: strText.Format(",3I0=%.2fA", wActData*0.0333333f); break;
    case PROTECTACT_U: strText.Format(",U=%.2fV", wActData*0.04f); break;
    }
    return strText;
}

void CMyUnitPM310::OnOpenList(CMyDataPMOPList* pOPList)
{
    CMyDlgOpList dlg;
    dlg.m_pOPList = pOPList;
    MyDoModal(&dlg,PM310DLL.hModule);
}

void CMyUnitPM310::ReceiveWaveRecordHeadList(COMCONTROL* pCC)
{
    int nHeadLen = 11 + WAVERECORD_DATASIZE;
    int nWaveLen = sizeof(WAVERECORDR)/sizeof(WORD);
    WAVERECORDR WaveRecord;
    CMyOpListArray arList;
    OPList List;
    for(int i=0;i<WAVERECORD_WAVENUM;i++)
    {
        if(MODBUS_Read(pCC,LOGADDR_WAVERECORD+i*nWaveLen,nHeadLen)) break;
        CopyByte2WORDHL((WORD*)&WaveRecord,pCCRX+3,nHeadLen);
        if(WaveRecord.wRecordStatus==0xffff && WaveRecord.wFreezeDotNo<=WAVERECORD_DOTNUM)
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
            List.nIndex = i;
            arList.Add(List);
        }
    }
    ASSERT(m_pWaveRecordList);
    m_pWaveRecordList->RefreshData(arList);
    m_bWaveRecordListOK = TRUE;
}

BOOL CMyUnitPM310::ReceiveWave(COMCONTROL* pCC, int nWaveNo)
{
    WAVERECORDR WaveRecord;
    nWaveNo %= WAVERECORD_WAVENUM;
    if(!ReceiveWaveRecordHead(pCC, nWaveNo, WaveRecord)) return FALSE;
    if(!ReceiveWaveRecordData(pCC, nWaveNo, WaveRecord)) return FALSE;
    SaveWave(WaveRecord);
    CString strMessage;
    strMessage.Format("接收故障录波结束,录波号:%d", nWaveNo);
    AddEvent(strMessage);
    return TRUE;
}

BOOL CMyUnitPM310::ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord)
{
    ASSERT(nWaveNo>=0 && nWaveNo<WAVERECORD_WAVENUM);
    int nHeadLen = 11 + WAVERECORD_DATASIZE;
    int nWaveLen = sizeof(WAVERECORDR)/sizeof(WORD);
    
    if(MODBUS_Read(pCC,LOGADDR_WAVERECORD+nWaveNo*nWaveLen,nHeadLen)) return FALSE;
    CopyByte2WORDHL((WORD*)&Waverecord, pCCRX+3, nHeadLen);
    if(Waverecord.wRecordStatus==0xffff && Waverecord.wFreezeDotNo<=WAVERECORD_DOTNUM)
    {
        CString strMessage;
        strMessage.Format("接收故障录波开始,录波号:%d",nWaveNo);
        AddEvent(strMessage);
        return TRUE;
    }
    return FALSE;
}

BOOL CMyUnitPM310::ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord)
{
    ASSERT(nWaveNo>=0 && nWaveNo<WAVERECORD_WAVENUM);
    int nHeadLen = 11 + WAVERECORD_DATASIZE;
    int nWaveLen = sizeof(WAVERECORDR)/sizeof(WORD);
    int nDataLen = nWaveLen - nHeadLen;
    int nDataRcv = 0;                     // 已读的时候数据
    while(nDataRcv<nDataLen)
    {
        int nData = nDataLen - nDataRcv;
        if(nData>100) nData = 100;
        if(MODBUS_Read(pCC, LOGADDR_WAVERECORD+nWaveNo*nWaveLen +nHeadLen+nDataRcv, nData)) return FALSE;
        CopyByte2WORDHL((WORD*)&Waverecord.nData[0]+nDataRcv, pCCRX+3, nData);
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

static const char* g_pszChannelName[] =
{
    _T("Ua:A相电压"),
    _T("Ub:B相电压"),
    _T("Uc:C相电压"),
    _T("Ia:A相电流"),
    _T("Ib:B相电流"),
    _T("Ic:C相电流"),
};

static const char* g_pszChannelUnit[] =
{
    _T("V"),
    _T("V"),
    _T("V"),
    _T("A"),
    _T("A"),
    _T("A"),
};


void CMyUnitPM310::SaveWave(WAVERECORDR& Waverecord)
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
    
    int nWaveRecordedDot = Waverecord.wFreezeDotNo;

    CTime time = CTime(wYear,wMonth,wDay,wHour,wMinute,wSecond);
    time -= 10L;                // -10s
    DWORD dwMilliSecond = 10000L + wMilliSecond;
    dwMilliSecond -= (nWaveRecordedDot-24*5)*(20)/(24);            // 冻结前(nWaveRecordedDot-24*5)点
//     dwMilliSecond -= nWaveRecordedDot*(20)/(24);                        // 冻结前(nWaveRecordedDot)点
    time += dwMilliSecond/1000;
    wMilliSecond = (WORD)(dwMilliSecond%1000);
    
    CMyWaveInfo waveinfo;
    waveinfo.Create(WAVERECORD_DATASIZE-1, 4, nWaveRecordedDot, 24*50);
    waveinfo.SetTime(time.GetTime(),wMilliSecond);
    
    for(int i=0;i<WAVERECORD_DATASIZE-1;++i)
    {
        SetWaveInfoAD(waveinfo,i,g_pszChannelName[i], g_pszChannelUnit[i], nWaveRecordedDot, Waverecord);
    }
    for(i=0;i<4;i++) SetWaveInfoDI(waveinfo, i, 1<<i, nWaveRecordedDot, Waverecord);
    
    waveinfo.StoreToFile(m_strName, strFileName);
}

void CMyUnitPM310::SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName, CString strUnitage,
                                   int nWaveRecordedDot, WAVERECORDR& Waverecord)
{
    waveinfo.SetChannelInfoAD(nChannelNo, strChannelName, strUnitage, 4096);
    float* pData = waveinfo.m_pDataAD + nWaveRecordedDot*nChannelNo;
    float fSum = 0;
    for(int i=0;i<nWaveRecordedDot;i++)
    {
        int nData;
        nData = Waverecord.nData[nChannelNo][i];
        pData[i] = (float)nData;
        fSum += (float)nData;
    }
    if(nWaveRecordedDot) fSum /= nWaveRecordedDot;
    for(i=0;i<nWaveRecordedDot;i++)
    {
        float fWaveData = pData[i] - fSum;
        fWaveData = fWaveData*Waverecord.nK[nChannelNo]*0.0001f;
        pData[i] = fWaveData;
    }
}

void CMyUnitPM310::SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, WAVERECORDR& Waverecord)
{
    ASSERT(nChannelNo>=0 && nChannelNo<12);
    
    CString strChannelName = g_pszInName[nChannelNo];
    waveinfo.SetChannelInfoDI(nChannelNo,strChannelName,"0","1");
    for(int i=0;i<nWaveRecordedDot;i++)
    {
        BYTE* pDataDI = waveinfo.m_pDataDI + nChannelNo*nWaveRecordedDot;
        pDataDI[i] = ((Waverecord.nData[WAVERECORD_DATASIZE-1][i]&wMask)==wMask);
    }
}