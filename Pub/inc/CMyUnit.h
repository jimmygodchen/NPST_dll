//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYUNIT_H
#define __CMYUNIT_H

// 通信地址:
// typedef struct
// {
//     BOOL bValidSrc;
//     BOOL bValidDest;
//     DWORD dwAddressSrc;
//     DWORD dwAddressDest;
//     DWORD dwMinAddressSrc;
//     DWORD dwMaxAddressSrc;
//     DWORD dwMinAddressDest;
//     DWORD dwMaxAddressDest;
// }COMADDRESS;

class CMyPort;

// 通信控制块:
typedef struct
{
    CMyPort* pPort;
    BYTE* pTXBuffer;
    BYTE* pRXBuffer;
}COMCONTROL;

#define pCCPort     (pCC->pPort)
#define pCCTX       (pCC->pTXBuffer)
#define pCCRX       (pCC->pRXBuffer)

//---------------------------------------------- CMyUnit ----------------------
class CLASS_EXPORT CMyUnit:public CMyObj
{
public:
    static CStringArray s_aType;
    static CMapStringToPtr s_mapTypeToClass;
    static void RegisterClass(CString strType, CRuntimeClass* pRuntimeClass);

public:
    DECLARE_SERIAL(CMyUnit);
    CMyUnit();
    ~CMyUnit();

public:
    CMyPort* m_pParentPort;                 // 所属父端口;
    CMyFactoryArray m_aFactory;             // 数据工厂集合;

public:
    CMyFactory* AddDataFactory(CRuntimeClass* pRuntimeClass,CString strField,BOOL bCreate = TRUE);
    CMyData* GetData(CString strField);
    void AddEvent(CString strEvent);
    virtual BOOL OnCreateData(CMyData* pData){ return TRUE; };
    virtual void ExchangeComData(COMCONTROL* pCC){};
    virtual void OnPortOpen(void){};
    virtual void OnPortClose(void){};
    virtual void OnEditMem(const CMyDataMem& Mem){};
};

typedef CTypedPtrList<CObList,CMyUnit*> CMyUnitList;
typedef CTypedPtrArray<CObArray,CMyUnit*> CMyUnitArray;


#endif/*__CMYUNIT_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

