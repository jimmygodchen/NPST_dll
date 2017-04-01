//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "CMyUnitModbus.h"
#include "CMyDlgUnitParam.h"

//---------------------------------------------- CMyUnitModbus -----------------------
IMPLEMENT_SERIAL(CMyUnitModbus,CMyUnit,0)

CMyUnitModbus::CMyUnitModbus():CMyUnit(),m_crc16(0x8005,TRUE)
{
    m_nAddr = 1;
    m_nTimeout = 1000;
    m_wTask = 0;
}

void CMyUnitModbus::Serialize(CArchive& ar)
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

BOOL CMyUnitModbus::OnAttrib(CBCGPPropertySheet& sheet)
{
    HINSTANCE hInstOld = AfxGetResourceHandle();
    AfxSetResourceHandle(PM310DLL.hModule);
    
    CMyDlgUnitParam pageNPS;
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

int CMyUnitModbus::ReadCom(COMCONTROL* pCC, BYTE* pBuff, int nLen)
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

int CMyUnitModbus::MODBUS_Read(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord)
{
    BYTE* pTX = pCCTX;
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x03;
    *pTX++ = BYTE(wBaseAddress>>8);
    *pTX++ = BYTE(wBaseAddress&0xff);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    WORD wCRC = 0xffff;
    m_crc16.CalculateCRC(pCCTX,pTX-pCCTX,wCRC);
    *pTX++ = BYTE(wCRC&0xff);
    *pTX++ = BYTE(wCRC>>8);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);
    int nLength = wCountWord*2+((wCountWord<=125)?5:6);
    int nLengthRead = 0;

    m_pParentPort->m_bAutoSndMsg = FALSE;
    nLengthRead += ReadCom(pCC, pCCRX, 2);
    if(nLengthRead<2)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }

    if((pCCRX[1]&0x80)) nLength = 8;
    nLengthRead += ReadCom(pCC, pCCRX+2, nLength - 2);
    m_pParentPort->m_bAutoSndMsg = TRUE;
    m_pParentPort->AddComReportRX(pCCRX, nLengthRead);

    if(nLengthRead<nLength)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }
    if(pCCRX[0]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }
    
    if((pCCRX[1]&0x7f)!=0x03)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr;
    }

    wCRC = 0xffff;
    m_crc16.CalculateCRC(pCCRX,nLength,wCRC);
    if(wCRC!=0)
    {
        AddEvent(_T("校验和出错!"));
        return COMERR_CRCErr;
    }

    if(pCCRX[1]&0x80) return COMERR_Nodata;

//     BYTE* pRX = (wCountWord<=125)?(pCCRX+3):(pCCRX+4);

    return COMERR_NoErr;
}

int CMyUnitModbus::MODBUS_Write(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord,WORD* pData)
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
    m_crc16.CalculateCRC(pCCTX,pTX-pCCTX,wCRC);
    *pTX++ = BYTE(wCRC&0xff);
    *pTX++ = BYTE(wCRC>>8);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);

    Sleep(300);

    if(m_nAddr==0) return TRUE;
    if(pCCPort->ReadCom(pCCRX,8)<8)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }
    
    if(pCCRX[0]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }
    
    if((pCCRX[1]&0x7f)!=0x10)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr;
    }

    wCRC = 0xffff;
    m_crc16.CalculateCRC(pCCRX,8,wCRC);
    if(wCRC!=0)
    {
        AddEvent(_T("校验和出错!"));
        return COMERR_CRCErr;
    }
    return COMERR_NoErr;
}

int CMyUnitModbus::MODBUS_Write(COMCONTROL* pCC, WORD wBaseAddress, WORD wData)
{
    return MODBUS_Write(pCC, wBaseAddress, 1, &wData);
}

void CMyUnitModbus::CopyByte2WORDHL(WORD* pwDest, BYTE* pSrc, WORD wWORDCount)             // 先高后低
{
    for(int i=0;i<wWORDCount;i++)
    {
        int nByteIndex = i<<1;
        pwDest[i] = pSrc[nByteIndex+1] + (((WORD)pSrc[nByteIndex]<<8)&0xff00);
    }
}

void CMyUnitModbus::CopyWORD2BYTEHL(BYTE* pDest, WORD* pwSrc, WORD wWORDCount)             // 先高后低
{
    for(int i=0;i<wWORDCount;i++)
    {
        int nByteIndex = i<<1;
        pDest[nByteIndex] = (BYTE)(pwSrc[i]>>8);
        pDest[nByteIndex+1] = (BYTE)pwSrc[i];
    }
}

void CMyUnitModbus::CopyStringToWSZ(WORD* pwszDest, CString strSrc)
{
    char* pszSrc = (char*)(const char*)strSrc;
    while(*pszSrc) *pwszDest++ = WORD(BYTE(*pszSrc++));
    *pwszDest = 0;
}

void CMyUnitModbus::CopyWSZToString(CString& strDest, WORD* pwszSrc)
{
    char szDest[200];
    char* pszDest = szDest;
    for(int i=0;i<199;i++)
    {
        if(*pwszSrc) *pszDest++ = char(*pwszSrc++);
        else break;
    }
    *pszDest = 0;
    strDest = szDest;
}

BYTE CMyUnitModbus::GetAnalogFormat(float fScale)
{
    if(fScale<=20.0f) return 0x03;
    else if(fScale<=200.0f) return 0x02;
    else if(fScale<=2000.0f) return 0x01;
    else return 0;
}

float CMyUnitModbus::GetAIFloat(float fScale, float fValue, float fK)
{
    BYTE Format = GetAnalogFormat(fScale);
    ASSERT(Format<4);
    for(int i=0;i<Format;++i) fValue *= 0.1f;
    fValue *= fK;
    return fValue;
}

float CMyUnitModbus::GetAIFloat(BYTE Format, float fValue, float fK)
{
    ASSERT(Format<4);
    for(int i=0;i<Format;++i) fValue *= 0.1f;
    fValue *= fK;
    return fValue;
}

void CMyUnitModbus::RefreshFloat(CMyDataFloat* pFloat, float fSacle, float fValue, float fK)
{
    if(pFloat==NULL) return;
    BYTE Format = GetAnalogFormat(fSacle);
    ASSERT(Format<4);
    for(int i=0;i<Format;++i) fValue *= 0.1f;
    fValue *= fK;
    pFloat->RefreshData(fValue);
}

void CMyUnitModbus::RefreshFloat(CMyDataFloat* pFloat, BYTE Format, float fValue, float fK)
{
    if(pFloat==NULL) return;
    ASSERT(Format<4);
    for(int i=0;i<Format;++i) fValue *= 0.1f;
    fValue *= fK;
    pFloat->RefreshData(fValue);
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



