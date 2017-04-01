//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYWAVEINFO_H
#define __CMYWAVEINFO_H

//---------------------------------------------- CMyWaveInfo ------------------
class CLASS_EXPORT CMyWaveInfo
{
public:
    CMyWaveInfo();
    ~CMyWaveInfo();

public:
    WORD m_wYear;               // 录波开始时刻:年;
    WORD m_wMonth;              // 录波开始时刻:月;
    WORD m_wDay;                // 录波开始时刻:日;
    WORD m_wHour;               // 录波开始时刻:时;
    WORD m_wMinute;             // 录波开始时刻:分;
    WORD m_wSecond;             // 录波开始时刻:秒;
    WORD m_wMilliSecond;        // 录波开始时刻:毫秒;
    BYTE m_NumChannelAD;        // 录波AD通道数;
    BYTE m_NumChannelDI;        // 录波DI通道数;
    WORD m_wDotPerChannel;      // 每个通道采样点数;
    WORD m_wFrequency;          // 采样频率(每周波12点=600);
    CStringArray m_astrNameAD;   // AD通道名称;
    CStringArray m_astrUnitageAD;// AD通道单位;
//     float m_fFullScaleAD[16];	// AD通道额定值;
    CStringArray m_astrNameDI;  // DI通道名称;
//     CString m_strStatus0DI[16]; // DI通道状态0名称;
//     CString m_strStatus1DI[16]; // DI通道状态1名称;
    float* m_pDataAD;      // AD录波数据;
    BYTE* m_pDataDI;       // DI录波数据;

public:
    void Create(BYTE NumChannelAD, BYTE NumChannelDI, WORD wDotPerChannel, WORD wFrequency);
    void SetTime(time_t timeStart, WORD wMilliSecond);
    void SetTime(WORD wYear,WORD wMonth,WORD wDay,WORD wHour,WORD wMinute,WORD wSecond,WORD wMilliSecond);
    void SetChannelInfoAD(BYTE ChannelNo,CString strName,CString strUnitage,float fFullScale);
    void SetChannelInfoDI(BYTE ChannelNo,CString strName,CString strStatus0,CString strStatus1);
    void Destroy(void);
    void LoadFromFile(CString strFileName);
    void StoreToFile(CString strUnitName,CString strFileName);
    CString GetFileName(void);
    BOOL IsWaveValid(void);
    BOOL Serialize(CArchive& ar);
};

#endif/*__CMYWAVEINFO_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

