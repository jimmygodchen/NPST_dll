//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAMEM_H
#define __CMYDATAMEM_H

// ---------------------------------------------- CMyDataMem -------------
class CLASS_EXPORT CMyDataMem:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataMem);
    CMyDataMem();
    ~CMyDataMem();
    
public:
    int m_nID;                      // 可用于指示CMyDataMem的用途
    int m_nSize;                    // 分配内存大小
    BOOL m_bOK;                     // 指示内存中数据是否有效
    void* m_pMemR;                  // 一般用于存放修改前数据
    void* m_pMemW;                  // 一般用于存放修改后数据
    
public:
    virtual void Initialize(CString strName, int nID, int nSize);
    virtual BOOL ExeOperate(void);
    virtual void RefreshData(const void* pMem);
    void StoreToDevice(const void* pMem);
    void OnOpen(CString strDevType, char* pczExtension, void* m_pMem);
    void OnSave(CString strDevType, CString strFileName, char* pczExtension, const void* pMem);
};

#endif/*__CMYDATAMEM_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

