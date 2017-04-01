//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYNPS7510_H
#define __CMYNPS7510_H

#define EVENT_COUNT			100
#define SWITCH_COUNT		12

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

#define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x00)	//三相PT断线;
#define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x01)	//两相PT断线;
#define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x02)	//单相PT断线;
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x03)    //控制回路断线;

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

//---------------------------------------------- CMyDataNPSParam -----------
typedef struct
{
    WORD wLCDContrast;					// LCD对比度
    WORD wszDeviceType[17];				// 设备名称
    WORD wMultiLanguage;				// 界面语言
    WORD wModbusAddr1;					// 通信地址
    WORD wBaudrate1;					// 通信速率
    WORD wReserved[11];					// 保留:具体型号特有参数
}DEVICEPARAM;

typedef struct
{
    WORD wToggleAlarmPT;			// PT断线告警
    WORD wModePT;
    WORD wScaleCT;
    WORD wScalePT;
}DEVICEPARAM_NPS;

class CMyDataNPSParam:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSParam);
    CMyDataNPSParam();

public:
    BOOL m_bOK;
    DEVICEPARAM m_deviceParamR;
    DEVICEPARAM m_deviceParamW;

public:
    virtual void RefreshData(DEVICEPARAM& DeviceParam);
    virtual void StoreToDevice(DEVICEPARAM& pDeviceParam);
    virtual BOOL ExeOperate(void);
};

//---------------------------------------------- CMyDataNPSRegulate -----------
typedef struct
{
    short nRegulateR;				//校正系数实部;
    short nRegulateX;				//校正系数虚部;
}REGULATE;

typedef struct
{
    REGULATE regulate[10];
}REGULATESET;

class CMyDataNPSRegulate:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSRegulate);
    CMyDataNPSRegulate();
    
public:
    BOOL m_bOK;
    REGULATESET m_RegulateR;
    REGULATESET m_RegulateW;
    
public:
    virtual void RefreshData(REGULATESET& Regulate);
    virtual void StoreToDevice(REGULATESET& Regulate);
    virtual BOOL ExeOperate(void);
};


//---------------------------------------------- CMyDataNPSSetpoint -----------
//-----------------------------------------------------------------------------
typedef struct
{
    WORD wLinkIN;					// 关联开关量;
    WORD wToggle;					// 开关量保护投退;
}INSETPOINT;

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wToggle[8];				// 保护投退;
    WORD wSetpointArea1[24];		// 保护定值区1;
    INSETPOINT INSetpoint[4];		// 开关量保护;
}DEVICESETPOINT;

typedef struct
{
    WORD wDL1_SetI;					// 电流I段电流;
    WORD wDL1_SetT;					// 电流I段时间;
    WORD wDL1_TogU;                 // 低压闭锁
    
    WORD wDL2_SetI;					// 电流II段电流;
    WORD wDL2_SetT;					// 电流II段时间;
    WORD wDL2_TogU;                 // 低压闭锁
    
    WORD wDL3_SetI;					// 电流III段电流;
    WORD wDL3_SetT;					// 电流III段时间;
    WORD wDL3_TogU;                 // 低压闭锁
    
    WORD wDL_SetU;                  // 电流保护闭锁电压
    
    WORD wLX1_SetI;				    // 零流I段电流;
    WORD wLX1_SetT;				    // 零流I段时间;
    
    WORD wLX2_SetI;				    // 零流I段电流;
    WORD wLX2_SetT;				    // 零流I段时间;
    
    WORD wGFH_SetI;				    // 过负荷电流;
    WORD wGFH_SetT;				    // 过负荷时间;
    //     WORD wGFH_GJ;                   // 告警
    
    WORD wDDY_SetU;					// 低电压电压;
    WORD wDDY_SetI;					// 低电压闭锁电流;
    WORD wDDY_SetT;					// 低电压时间;
}DEVICESETPOINT_NPS;

class CMyDataNPSSetpoint:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSSetpoint);
    CMyDataNPSSetpoint();
    
public:
    BOOL m_bOK;
    DEVICESETPOINT m_SetpointR;
    DEVICESETPOINT m_SetpointW;
    
public:
    virtual void RefreshData(DEVICESETPOINT& Setpoint);
    virtual void StoreToDevice(DEVICESETPOINT& Setpoint);
    virtual BOOL ExeOperate(void);
};

//---------------------------------------------- CMyDataNPSYC -----------
class CMyDataNPSYC:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSYC);
    CMyDataNPSYC();

public:
//     virtual void RefreshData(DEVICEPARAM& DeviceParam);
//     virtual void StoreToDevice(DEVICEPARAM& pDeviceParam);
    virtual BOOL ExeOperate(void);
};


// ----------------------CMyDataOPList-------------------------------------------
// 用于Server与HMI之间交互List数据
// 主要用于读取历史故障录波和示波器数据
typedef struct
{
    CString strName;
    int nIndex;
}OPList;

class CMyDataOPList:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataOPList);
    CMyDataOPList();
    
public:
    // 读取历史故障录波信息
    CArray<OPList,OPList> m_arOPList;
    int m_nOPIndex;					// 要读取数据编号
    
public:
//     void SerializeDynInfo(CArchive& ar,int nDynInfoMode);
    void RefreshData(CArray<OPList,OPList>& arOpList);
    void SndCmd(int nOPIndex,BYTE Cmd=0xff);
    BOOL ExeOperate(void);
};


#define WAVERECORD_WAVECNT  10                  // 周波数
#define WAVERECORD_DOTNUM   (24*WAVERECORD_WAVECNT)
#define WAVERECORD_WAVENUM  2

#define WAVERECORD_DATASIZE     6               //每个录波点数据大小;

typedef struct
{
    DEVICETIME timeFreeze;                              //录波器录波冻结时间;
    WORD wRecordStatus;                                 //录波器当前录波状态;
    WORD wFreezeDotNo;                                  //录波器录波冻结点号;
    WORD wCycleFlag;                                    //录波器是否循环标志;
    WORD wData[WAVERECORD_DOTNUM][WAVERECORD_DATASIZE]; //录波器录波数据;
}WAVERECORD;


//---------------------------------------------- CMyUnitNPS7510 ----------------------
class CMyUnitNPS7510:public CMyUnit
{
public:
    DECLARE_SERIAL(CMyUnitNPS7510);
    CMyUnitNPS7510();
    ~CMyUnitNPS7510();

protected:
    CMyCommDispatch m_commdispatch;

public:
    virtual BOOL OnAttrib(CBCGPPropertySheet& sheet);
    virtual void ExchangeComData(COMCONTROL* pCC);

public:
    int m_nAddr;
    int m_nTimeout;
    BOOL m_bInfoOK;
    BOOL m_bParamOK;
    BOOL m_bRegulateOK;
    BOOL m_bSetpointOK;
    BOOL m_bWaveRecordListOK;
    BOOL m_bTimeSyn;

//     WORD m_wCountInfo;
    WORD m_wCountParam;
    WORD m_wCountRegulate;
    WORD m_wCountRegulateOld;
    WORD m_wCountParamOld;
    WORD m_wCountSetpoint;
    WORD m_wCountSetpointOld;
    WORD m_wCountEvent;
    WORD m_wCountEventOld;
    WORD m_wCountWaveRecord;
    WORD m_wCountWaveRecordOld;

//     int m_nWaveNo;                      // 读取故障录波序号
//     int m_nWaveFrames;                  // 读取故障录波

public:
    virtual void Serialize(CArchive& ar);

public:
    CMyDataFloat* m_pIa;
    CMyDataFloat* m_pIb;
    CMyDataFloat* m_pIc;
    CMyDataFloat* m_pIA;
    CMyDataFloat* m_pIC;
    CMyDataFloat* m_pUa;
    CMyDataFloat* m_pUb;
    CMyDataFloat* m_pIB;
    CMyDataFloat* m_pUc;
    CMyDataFloat* m_pUab;
    CMyDataFloat* m_pUbc;
    CMyDataFloat* m_pUca;
    CMyDataFloat* m_p3I0;
    CMyDataFloat* m_pF;
    CMyDataFloat* m_pP;
    CMyDataFloat* m_pQ;
    CMyDataFloat* m_pPF;

    CMyDataBin* m_pBi[12];
    CMyDataNPSYC* m_pYC[6];

    CMyDataOperate* m_pOP[5];

    CMyDataNPSParam* m_pParam;
    CMyDataNPSRegulate* m_pRegulate;
    CMyDataNPSSetpoint* m_pSetpoint;
    CMyDataOPList* m_pWaveRecordList;

public:
    virtual BOOL OnCreate(void);
    virtual BOOL OnCreateData(CMyData* pData);
    virtual void OnPortOpen(void);
//      virtual void OnPortClose(void){};

public:
    BOOL MODBUS_Read(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord);
    BOOL MODBUS_Write(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord,WORD* pData);
    BOOL ReadCom(COMCONTROL* pCC, BYTE* pBuff, int nLen);

public:
    void ReceiveInfo(COMCONTROL* pCC);
    void ReceiveParam(COMCONTROL* pCC);
    void ReceiveRegulate(COMCONTROL* pCC);
    void ReceiveSetpoint(COMCONTROL* pCC);
    void ReceiveAnalog(COMCONTROL* pCC);
    void ReceiveWaveRecordHeadList(COMCONTROL* pCC);
    void ReceiveEventTable(COMCONTROL* pCC);
    void TimeSyn(COMCONTROL* pCC);
    BOOL ReceiveWave(COMCONTROL* pCC, int nWaveNo);
    BOOL ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORD& Waverecord);
    BOOL ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORD& Waverecord);

public:
    void OnEditDeviceParam(CMyDataNPSParam* pDataParam);
    void OnEditRegulate(CMyDataNPSRegulate* pDataRegulate);
    void OnEditSetpoint(CMyDataNPSSetpoint* pDataSetpoint);
    void OnExcuteYC(CMyDataNPSYC* pDataYC);
    void OnOpenList(CMyDataOPList* pOPList);

    CString GetEventText(EVENT& Event);
    CString GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData);
    void SaveWave(WAVERECORD& Waverecord);
    void GetWaveRecordMetrics(int nIndex,CString& strChannelName,float& fFullScale,float& fFullScaleAD,float& fReg);
    void SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName,float fFullScale,float fFullScaleAD,
        int nWaveRecordedDot, int nWaveStartDotNo, WAVERECORD& Waverecord, float fReg);
    WORD GetWaveAIData(short nChIndex, WORD* pwData);
    void SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, int nWaveStartDotNo, WAVERECORD& Waverecord);

};

#endif/*__CMYNPS7510_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

