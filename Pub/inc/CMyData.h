//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATA_H
#define __CMYDATA_H

class CMyUnit;
class CMyData;

//---------------------------------------------- CMyData ----------------------
class CLASS_EXPORT CMyData:public CMyObj
{
public:
    static CStringArray s_aType;
    static CStringArray s_aBaseType;
    static CMapStringToPtr s_mapTypeToClass;
    static void RegisterClass(CString strType,CRuntimeClass* pRuntimeClass,BOOL bBaseType=FALSE);
    static CString GetType(CRuntimeClass* pRuntimeClass);
    static CString GetBaseType(CString strType);
    static CRuntimeClass* GetBaseClass(CRuntimeClass* pRuntimeClass);

public:
    DECLARE_SERIAL(CMyData);
    CMyData();

public:
    CString m_strField;				// 字段名;
    CString m_strName;				// 中文名称;
//     BYTE m_SaveDataMode;			// 保存数据;

public:
    CMyUnit* m_pParentUnit;			// 所属父单元;
    DWORD m_dwUpdateID;				// 数据更新标识;

public:
    void IncrementUpdateID(void);
    CString GetFullName(void);
    CString GetFieldAndName(void);

public:
    virtual void Initialize(CString strName);
//     virtual void Serialize(CArchive& ar);
//     virtual void SerializeDynInfo(CArchive& ar,int nDynInfoMode){};
//     virtual BOOL OnAttrib(void);
//     virtual BOOL OnAttrib(CPropertySheet& sheet);
//     virtual BOOL OnUpdateAttrib(void){ return TRUE; };
//     virtual void GetParamHead(CStringArray& aParamHead);
//     virtual void GetParamInfo(CStringArray& aParamInfo);
// public:
//     virtual void SaveData(CMySaveInfo* pSaveInfo){};
//     virtual void OnTimerHMI(void){};
// public:
//     virtual void GetStatusHead(CStringArray& aStatusHead,CMyDataArray& aData){};
//     virtual void GetStatusInfo(int nStatusIndex,BYTE& Status){};
//     virtual CMyData* GetDoubleHead(void){ return NULL; };
//     virtual double GetDoubleInfo(void){ return 0; };
// public:
//     virtual void GetOperateHeadManual(CStringArray& aOperateHead,CMyDataArray& aData){};
//     virtual void OnOperateManual(CString strOperateHead){};
//     virtual void GetOperateHeadAuto(CStringArray& aOperateHead,CMyDataArray& aData){};
//     virtual void OnOperateAuto(CString strOperateHead,CString strAutoOperator){};
// public:
//     virtual BOOL AllowLinkedbyYKYT(void){ return FALSE; };
//     virtual BOOL AllowOperateYKYT0(void){ return FALSE; };
//     virtual BOOL AllowOperateYKYT1(void){ return FALSE; };
//     virtual BOOL AllowLinkedbySetdata(void){ return FALSE; };
};

typedef CTypedPtrList<CObList,CMyData*> CMyDataList;
typedef CTypedPtrArray<CObArray,CMyData*> CMyDataArray;

#endif/*__CMYDATA_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

