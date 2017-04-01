//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYPM310_H
#define __CMYPM310_H

#define SWITCH_COUNT            4

// #define EVENT_COUNT			100

#define EVENTTYPE_NULL		0x0000		//空事件
#define EVENTTYPE_SWITCH	0x0001		//开关变位事件
#define EVENTTYPE_RUNINFO	0x0002		//运行信息事件
#define EVENTTYPE_ALARMED	0x0003		//设备告警事件
#define EVENTTYPE_TRIPPED	0x0004		//设备故障事件
#define EVENTTYPE_OPERATE	0x0005		//操作记录事件
#define EVENTTYPE_ERRORED	0x0006		//自检异常事件
#define EVENTTYPE_NOTUSED	0x0007		//无效事件

#define EVENTCODE_NULL					//空事件代码
#define EVENTCODE_OTHER		0x0100		//设备相关事件
#define EVENTCODE_SWITCH	0x0200		//开关量变位事件
#define EVENTCODE_ALARMED	0x0300		//告警检测事件
#define EVENTCODE_PROTECT	0x0400		//保护动作事件
#define EVENTCODE_ERRORED	0x0500		//自检异常事件
#define EVENTCODE_LAD		0x0600		//梯形图事件
#define EVENTCODE_REMOTE	0x0700		//遥控操作事件

// #define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x00)	//三相PT断线;
// #define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x01)	//两相PT断线;
// #define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x02)	//单相PT断线;
// #define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x03)    //控制回路断线;
// 
//-----------------------------------------------------------------------------
typedef struct _DEVICETIME
{
    WORD wYear;						//年(实际年-2000,0-100);
    WORD wMonth;					//月(1-12);
    WORD wDay;						//日(1-31);
    WORD wHour;						//时(0-23);
    WORD wMinute;					//分(0-59);
    WORD wSecond;					//秒(0-59);
    WORD wMilliSecond;				//毫秒(0-999);
}DEVICETIME;

typedef struct _EVENT
{
    DEVICETIME time;				//事件发生的时间戳;
    WORD wType;						//事件类型;
    WORD wCode;						//事件代码;
    WORD wData;						//相关数据,其含义取决于事件代码;
}EVENT;

//---------------------------------------------- CMyDataPMParam -----------
typedef struct
{
    WORD wLCDContrast;					// LCD对比度
    WORD wszDeviceType[17];				// 设备名称
    WORD wMultiLanguage;				// 界面语言
    WORD wModbusAddr1;					// 通信地址
    WORD wBaudrate1;					// 通信速率
    WORD wReserved[11];					// 保留:具体型号特有参数
}tDEVICEPARAM;

typedef struct
{
    WORD wToggleAlarmPT;                // PT断线告警
    WORD wModePT;
    WORD wScaleCT;
    WORD wScalePT;
    WORD wSLType;
}tDEVICEPARAM_PM;

class CMyDataPMParam:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMParam);
    CMyDataPMParam();

public:
    BOOL m_bOK;
    tDEVICEPARAM m_deviceParamR;
    tDEVICEPARAM m_deviceParamW;

public:
    virtual void RefreshData(tDEVICEPARAM& DeviceParam);
    virtual void StoreToDevice(tDEVICEPARAM& pDeviceParam);
    virtual BOOL ExeOperate(void);
};

//---------------------------------------------- CMyDataPMRegulate -----------
typedef struct
{
    short nRegulateR;				//校正系数实部;
    short nRegulateX;				//校正系数虚部;
}REGULATE;

typedef struct
{
    REGULATE regulate[6];
}tREGULATESET;

class CMyDataPMRegulate:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMRegulate);
    CMyDataPMRegulate();
    
public:
    BOOL m_bOK;
    tREGULATESET m_RegulateR;
    tREGULATESET m_RegulateW;
    
public:
    virtual void RefreshData(tREGULATESET& Regulate);
    virtual void StoreToDevice(tREGULATESET& Regulate);
    virtual BOOL ExeOperate(void);
};


//---------------------------------------------- CMyDataPMSetpoint -----------
//-----------------------------------------------------------------------------
typedef struct
{
    WORD wConfig;					// 保护配置;
    WORD wLinkIN;					// 关联开关量;
    WORD wToggle;					// 开关量保护投退;
}INSETPOINT;

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wConfig[6];			    // 保护配置;
    WORD wToggle[6];				// 保护投退;
    WORD wSetpointArea1[24];		// 保护定值区1;
    INSETPOINT INSetpoint[4];		// 开关量保护;
}tDEVICESETPOINT;

typedef struct
{
    WORD wDL1_SetI;					// 电流I段电流;
    WORD wDL1_SetT;					// 电流I段时间;

    WORD wDL2_SetI;					// 电流II段电流;
    WORD wDL2_SetT;					// 电流II段时间;

    WORD wGY1_SetU;					// 过压I段电流;
    WORD wGY1_SetT;					// 过压I段时间;

    WORD wGY2_SetU;					// 过压II段电流;
    WORD wGY2_SetT;					// 过压II段时间;

    WORD wQY1_SetU;					// 欠压I段电流;
    WORD wQY1_SetT;					// 欠压I段时间;

    WORD wQY2_SetU;					// 欠压II段电流;
    WORD wQY2_SetT;					// 欠压II段时间;
}tDEVICESETPOINT_PM;

class CMyDataPMSetpoint:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMSetpoint);
    CMyDataPMSetpoint();
    
public:
    BOOL m_bOK;
    tDEVICESETPOINT m_SetpointR;
    tDEVICESETPOINT m_SetpointW;
    
public:
    virtual void RefreshData(tDEVICESETPOINT& Setpoint);
    virtual void StoreToDevice(tDEVICESETPOINT& Setpoint);
    virtual BOOL ExeOperate(void);
};

// //---------------------------------------------- CMyDataNPSYC -----------
// class CMyDataNPSYC:public CMyDataOperate
// {
// protected:
//     DECLARE_SERIAL(CMyDataNPSYC);
//     CMyDataNPSYC();
// 
// public:
// //     virtual void RefreshData(DEVICEPARAM& DeviceParam);
// //     virtual void StoreToDevice(DEVICEPARAM& pDeviceParam);
//     virtual BOOL ExeOperate(void);
// };

// ----------------------CMyDataPMOPList-------------------------------------------
// 用于Server与HMI之间交互List数据
// 主要用于读取历史故障录波和示波器数据

typedef struct
{
    CString strName;
    int nIndex;
}OPList;

typedef CArray<OPList, OPList&> CMyOpListArray;

class CMyDataPMOPList:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMOPList);
    CMyDataPMOPList();

public:
    // 读取历史故障录波信息
    CMyOpListArray m_arOPList;
    int m_nOPIndex;                     // 要读取数据编号

public:
//     void SerializeDynInfo(CArchive& ar,int nDynInfoMode);
    void RefreshData(CMyOpListArray& arOpList);
    void SndCmd(int nOPIndex,BYTE Cmd=0xff);
    BOOL ExeOperate(void);
};

#define WAVERECORD_WAVECNT  10                  // 周波数
#define WAVERECORD_DOTNUM   (24*WAVERECORD_WAVECNT)
#define WAVERECORD_WAVENUM  5

#define WAVERECORD_DATASIZE     7               //每个录波点数据大小;

typedef struct
{
    DEVICETIME timeFreeze;                              // 录波器录波冻结时间;
    WORD wRecordStatus;                                 // 录波器当前录波状态;
    WORD wFreezeDotNo;                                  // 录波器录波冻结点号;
    WORD wCycleFlag;                                    // 录波器是否循环标志;
    short nK[WAVERECORD_DATASIZE];                      // 校正系数
    WORD wOffset;                                       // 直流分量
    short nData[WAVERECORD_DATASIZE][WAVERECORD_DOTNUM]; // 录波器录波数据;
}WAVERECORDR;


//---------------------------------------------- CMyUnitPM310 ----------------------
class CMyUnitPM310:public CMyUnitModbus
{
public:
    DECLARE_SERIAL(CMyUnitPM310);
    CMyUnitPM310();
    ~CMyUnitPM310();

public:
    virtual BOOL OnCreate(void);
    virtual BOOL OnCreateData(CMyData* pData);
    virtual void OnPortOpen(void);
    virtual void ExchangeComData(COMCONTROL* pCC);

public:
    BOOL m_bInfoOK;
    BOOL m_bTimeSyn;
    BOOL m_bParamOK;
    BOOL m_bRegulateOK;
    BOOL m_bSetpointOK;
    BOOL m_bWaveRecordListOK;

    WORD m_wCountParam;
    WORD m_wCountParamOld;
    WORD m_wCountRegulate;
    WORD m_wCountRegulateOld;
    WORD m_wCountSetpoint;
    WORD m_wCountSetpointOld;
    WORD m_wCountWaveRecord;
    WORD m_wCountWaveRecordOld;

public:
    const float m_fScaleI;
    const float m_fScaleUll;

public:
//     CMyDataFloat* m_pIa;
//     CMyDataFloat* m_pAngIa;
//     CMyDataFloat* m_pIb;
//     CMyDataFloat* m_pAngIb;
//     CMyDataFloat* m_pIc;
//     CMyDataFloat* m_pAngIc;
// 
//     CMyDataFloat* m_pUa;
//     CMyDataFloat* m_pUb;
//     CMyDataFloat* m_pUc;
//     CMyDataFloat* m_pUab;
//     CMyDataFloat* m_pUbc;
//     CMyDataFloat* m_pUca;
//     CMyDataFloat* m_pAngUa;
//     CMyDataFloat* m_pAngUb;
//     CMyDataFloat* m_pAngUc;
//     CMyDataFloat* m_pAngUab;
//     CMyDataFloat* m_pAngUbc;
//     CMyDataFloat* m_pAngUca;

    CMyDataVector* m_pIa;
    CMyDataVector* m_pIb;
    CMyDataVector* m_pIc;
    CMyDataVector* m_pUa;
    CMyDataVector* m_pUb;
    CMyDataVector* m_pUc;
    CMyDataVector* m_pUab;
    CMyDataVector* m_pUbc;
    CMyDataVector* m_pUca;

    CMyDataFloat* m_pFreq;
    CMyDataFloat* m_pP;
    CMyDataFloat* m_pQ;
    CMyDataFloat* m_pS;
    CMyDataFloat* m_pPF;

    CMyDataFloat* m_pEpimp;
    CMyDataFloat* m_pEqimp;
    CMyDataFloat* m_pEpexp;
    CMyDataFloat* m_pEqexp;

    CMyDataString* m_pCRCInfo;

public:
//     CMyDataFloat* m_pIa;
//     CMyDataFloat* m_pIb;
//     CMyDataFloat* m_pIc;
//     CMyDataFloat* m_pIA;
//     CMyDataFloat* m_pIC;
//     CMyDataFloat* m_pUa;
//     CMyDataFloat* m_pUb;
//     CMyDataFloat* m_pIB;
//     CMyDataFloat* m_pUc;
//     CMyDataFloat* m_pUab;
//     CMyDataFloat* m_pUbc;
//     CMyDataFloat* m_pUca;
//     CMyDataFloat* m_p3I0;
//     CMyDataFloat* m_pF;
//     CMyDataFloat* m_pP;
//     CMyDataFloat* m_pQ;
//     CMyDataFloat* m_pPF;

    CMyDataBin* m_pBi[SWITCH_COUNT];

    CMyDataOperate* m_pOpInitDevice;
    CMyDataOperate* m_pOpReset;
    CMyDataOperate* m_pOpFreezeWave;
    CMyDataOperate* m_pOpAdjust;
    CMyDataOperate* m_pOpTimesyn;

    CMyDataPMParam* m_pParam;
    CMyDataPMRegulate* m_pRegulate;
    CMyDataPMSetpoint* m_pSetpoint;
    CMyDataPMOPList* m_pWaveRecordList;

public:
    void ReceiveInfo(COMCONTROL* pCC);
    void TimeSyn(COMCONTROL* pCC);
    void ReceiveParam(COMCONTROL* pCC);
    void ReceiveRegulate(COMCONTROL* pCC);
    void ReceiveSetpoint(COMCONTROL* pCC);
    void ReceiveAnalog(COMCONTROL* pCC);
    void ReceiveAnalogExt(COMCONTROL* pCC);
    void ReceiveWaveRecordHeadList(COMCONTROL* pCC);
    void ReceiveEventTable(COMCONTROL* pCC);
    BOOL ReceiveWave(COMCONTROL* pCC, int nWaveNo);
    BOOL ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);
    BOOL ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);

public:
    void OnEditDeviceParam(CMyDataPMParam* pDataParam);
    void OnEditRegulate(CMyDataPMRegulate* pDataRegulate);
    void OnEditSetpoint(CMyDataPMSetpoint* pDataSetpoint);
//     void OnExcuteYC(CMyDataNPSYC* pDataYC);
    void OnOpenList(CMyDataPMOPList* pOPList);

    CString GetEventText(EVENT& Event);
    CString GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData);
    void SaveWave(WAVERECORDR& Waverecord);
    void SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName, CString strUnitage,
        int nWaveRecordedDot, WAVERECORDR& Waverecord);
    void SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, WAVERECORDR& Waverecord);

};

#endif/*__CMYPM310_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

