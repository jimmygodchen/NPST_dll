//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYUNITMODBUS_H
#define __CMYUNITMODBUS_H

enum COMERR
{
    COMERR_NoErr = 0,
    COMERR_Nodata,
    COMERR_Timeout,
    COMERR_AddrErr,
    COMERR_FunErr,
    COMERR_CRCErr,
};

class CMyUnitModbus:public CMyUnit
{
public:
    DECLARE_SERIAL(CMyUnitModbus);
    CMyUnitModbus();

public:
    virtual BOOL OnAttrib(CBCGPPropertySheet& sheet);
    virtual void Serialize(CArchive& ar);

public:
    int m_nAddr;
    int m_nTimeout;
    CMyCRC16 m_crc16;
    WORD m_wTask;
    
public:
    int MODBUS_Read(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, WORD* pData);
    int MODBUS_Write(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord,WORD* pData);
    int MODBUS_Write(COMCONTROL* pCC, WORD wBaseAddress, WORD wData);
    int ReadCom(COMCONTROL* pCC, BYTE* pBuff, int nLen);

public:
    static void CopyByte2WORDHL(WORD* pwDest, BYTE* pSrc, WORD wWORDCount);             // 先高后低
    static void CopyWORD2BYTEHL(BYTE* pDest, WORD* pwSrc, WORD wWORDCount);             // 先高后低
    static void CopyStringToWSZ(WORD* pwszDest,CString strSrc);
    static void CopyWSZToString(CString& strDest,WORD* pwszSrc);

public:
    BYTE GetAnalogFormat(float fScale);
    float GetAIFloat(float fScale, float fValue, float fK=1.0f);
    float GetAIFloat(BYTE Format, float fValue, float fK=1.0f);
    void RefreshFloat(CMyDataFloat* pFloat, float fSacle, float fValue, float fK=1.0f);
    void RefreshFloat(CMyDataFloat* pFloat, BYTE Format, float fValue, float fK=1.0f);
};

#endif /*__CMYUNITMODBUS_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



