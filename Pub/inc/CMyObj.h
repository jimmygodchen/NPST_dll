//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYOBJ_H
#define __CMYOBJ_H

//---------------------------------------------- CMyObj -----------------------
class CLASS_EXPORT CMyObj:public CObject
{
public:
    DECLARE_SERIAL(CMyObj);
    CMyObj();

protected:
    CCriticalSection m_critical;
//     CString m_strError;                 // 异常信息;

public:
//     BOOL m_bUsed;                       // 投入使用标志;
    int m_nID;
    CString m_strType;                  // 类型;
    CString m_strName;                  // 名称(唯一);

public:
    virtual BOOL OnCreate(void){ return TRUE; };
    virtual void Serialize(CArchive& ar);
    virtual BOOL OnAttrib(void);
    virtual BOOL OnAttrib(CBCGPPropertySheet& sheet);
    virtual CString GetFullName(void);
    virtual void GetParamHead(CStringArray& aParamHead){};
    virtual void GetParamInfo(CStringArray& aParamInfo){};

public:
    virtual void Load(void);
    virtual void Store(void);
    virtual CString GetFileName(void);

// public:
//     void ClearError(void);
//     void SetError(CString strError);
//     CString GetLastError(void);

// public:
//     virtual void OnTimerFast(void){};
//     virtual void OnTimer1Sec(void){};
//     virtual void OnTimer5Sec(void){};
//     virtual void OnTimer1Min(void){};
//     virtual void OnTimer1Hour(void){};
};

typedef CTypedPtrList<CObList,CMyObj*> CMyObjList;
typedef CTypedPtrArray<CObArray,CMyObj*> CMyObjArray;


#endif/*__CMYOBJ_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

