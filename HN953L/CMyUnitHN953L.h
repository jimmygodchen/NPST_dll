//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYUNITHN953L_H
#define __CMYUNITHN953L_H

//-----------------------------------------------------------------------------
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

typedef struct
{
    DEVICETIME time;				//事件发生的时间戳;
    WORD wType;						//事件类型;
    WORD wCode;						//事件代码;
    WORD wData;						//相关数据,其含义取决于事件代码;
}tEVENT;

typedef struct
{
    WORD wLCDContrast;					// LCD对比度
    WORD wszDeviceType[17];				// 设备名称
    WORD wMultiLanguage;				// 界面语言
    WORD wModbusAddr1;					//通信地址
    WORD wBaudrate1;					//通信速率
    WORD wReserved[11];					// 保留:具体型号特有参数
}tDEVICEPARAM;

typedef struct
{
    WORD wToggleAlarmPT;			// PT断线告警
    WORD wModePT;
    WORD wScaleCT;
    WORD wScalePT;
    WORD wSLType;
    WORD wDevLocal;
}tDEVICEPARAM_NPS;

typedef struct
{
    short nRegulateR;				//校正系数实部;
    short nRegulateX;				//校正系数虚部;
}tREGULATE;

#define DFT_CHANNEL_HARD    11

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wLinkIN;					// 关联开关量;
    WORD wToggle;					// 开关量保护投退;
}tINSETPOINT;

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wToggle[10];                   // 保护投退;
    WORD wSetpointArea1[32];            // 保护定值区;
    tINSETPOINT INSetpoint[4];           // 开关量保护;
}tDEVICESETPOINT;

typedef struct
{
    WORD wBZT_Mode;                 // 备自投方式
    WORD wBZT_MLSetUh;              // 母联有压定值
    WORD wBZT_MLSetUl;              // 母联失压定值
    WORD wBZT_SetUh1;               // 1母有压定值
    WORD wBZT_SetUl1;               // 1母失压定值
    WORD wBZT_SetUh2;               // 2母有压定值
    WORD wBZT_SetUl2;               // 2母失压定值
    WORD wBZT_SetI1;                // 1母无流定值
    WORD wBZT_SetI2;                // 2母无流定值
    WORD wBZT_SetTL1;               // 跳1DL时间
    WORD wBZT_SetTL2;               // 跳2DL时间
    WORD wBZT_SetT;                 // 备自投时间
    
    WORD wDL1_SetI;                 // 电流I段电流;
    WORD wDL1_SetT;                 // 电流I段时间;
    WORD wDL1_TogU;                 // 低压闭锁
    
    WORD wDL2_SetI;                 // 电流II段电流;
    WORD wDL2_SetT;                 // 电流II段时间;
    WORD wDL2_TogU;                 // 低压闭锁
    
    WORD wDL3_SetI;                 // 电流III段电流;
    WORD wDL3_SetT;                 // 电流III段时间;
    WORD wDL3_TogU;                 // 低压闭锁
    
    WORD wDL_SetU;                  // 电流保护闭锁电压
    
    WORD wLX1_SetI;                 // 零流I段电流;
    WORD wLX1_SetT;                 // 零流I段时间;
    
    WORD wLX2_SetI;                 // 零流I段电流;
    WORD wLX2_SetT;                 // 零流I段时间;
    
    WORD wSY_SetU;					// 失压电压;
    WORD wSY_SetI;					// 失压闭锁电流;
    WORD wSY_SetT;					// 失压时间;
}tDEVICESETPOINTNPS;

// ----------------------CMyDataHN953OPList-------------------------------------------
typedef struct
{
    CString strName;
    int nIndex;
}OPList;

typedef CArray<OPList, OPList&> CMyOpListArray;

class CMyDataHN953OPList:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataHN953OPList);
    CMyDataHN953OPList();
    
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

#define WAVERECORD_WAVECNT      10                  // 周波数
#define WAVERECORD_DOTNUM       (24*WAVERECORD_WAVECNT)
#define WAVERECORD_WAVENUM      5

#define WAVERECORD_DATASIZE     10               //每个录波点数据大小;

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


//---------------------------------------------- CMyDataHN953YK -----------
class CMyDataHN953YK:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataHN953YK);
    CMyDataHN953YK();
    
public:
    virtual BOOL ExeOperate(void);
};


//---------------------------------------------- CMyUnitHN953L ----------------------
class CMyUnitHN953L:public CMyUnitModbus
{
public:
    DECLARE_SERIAL(CMyUnitHN953L);
    CMyUnitHN953L();
    ~CMyUnitHN953L();

public:
    const float m_fScaleIM;
    const float m_fScaleIP;
    const float m_fScaleUll;

public:
    CMyDataString* m_pCRCInfo;
    CMyDataBin* m_pBI[17];
    CMyDataVector* m_pVector[14];
    CMyDataFloat* m_pFloat[4];

    CMyDataHN953YK* m_pYK[6];

    CMyDataOperate* m_pInitDev;
    CMyDataOperate* m_pResetDev;
    CMyDataOperate* m_pFreezeRecord;
    CMyDataOperate* m_pAdjust;
    CMyDataOperate* m_pTimesyn;

    CMyDataMem* m_pParam;
    CMyDataMem* m_pRegulate;
    CMyDataMem* m_pSetpoint;
    CMyDataHN953OPList* m_pWaveRecordList;
    CMyRTWave* m_pRTWave;

public:
    int m_nTask;
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
    virtual BOOL OnCreate(void);
    virtual BOOL OnCreateData(CMyData* pData);
    virtual void OnPortOpen(void);
    virtual void ExchangeComData(COMCONTROL* pCC);

public:
    virtual void OnEditMem(const CMyDataMem& Mem);

public:
    void ReceiveInfo(COMCONTROL* pCC);
    void TimeSyn(COMCONTROL* pCC);
    void ReceiveParam(COMCONTROL* pCC);
    void ReceiveRegulate(COMCONTROL* pCC);
    void ReceiveSetpoint(COMCONTROL* pCC);
    void ReceiveAnalog(COMCONTROL* pCC);
    void ReceiveAnalogExt(COMCONTROL* pCC);
    void ReceiveEventTable(COMCONTROL* pCC);
    void ReceiveWaveRecordHeadList(COMCONTROL* pCC);
    void ReceiveRTWave(COMCONTROL* pCC);

    BOOL ReceiveWave(COMCONTROL* pCC, int nWaveNo);
    BOOL ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);
    BOOL ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);

public:
    void OnOpenList(CMyDataHN953OPList* pOPList);
    CString GetEventText(tEVENT& Event);
    CString GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData);
    void SaveWave(WAVERECORDR& Waverecord);
    void SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName, CString strUnitage,
        int nWaveRecordedDot, WAVERECORDR& Waverecord);
    void SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, WAVERECORDR& Waverecord);
    float GetChK(int nChIndex);

};

#endif/*__CMYUNITHN953L_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

