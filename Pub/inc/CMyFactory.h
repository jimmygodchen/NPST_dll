//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYFACTORY_H
#define __CMYFACTORY_H

//---------------------------------------------- CMyFactory -------------------
class CLASS_EXPORT CMyFactory:public CMyObj
{
public:
    DECLARE_SERIAL(CMyFactory);
    CMyFactory();
    ~CMyFactory();

public:
    CString m_strType;
    CString m_strField;
    CMyData* m_pData;

public:
//     virtual void Serialize(CArchive& ar);
//     virtual BOOL OnAttrib(void);
//     virtual BOOL OnUpdateAttribe(void){ return (m_pData)?TRUE:FALSE; };
//     virtual void GetParamHead(CStringArray& aParamHead);
//     virtual void GetParamInfo(CStringArray& aParamInfo);
    void DeleteData(void);
    CMyData* CreateData(void);

};

typedef CTypedPtrList<CObList,CMyFactory*> CMyFactoryList;
typedef CTypedPtrArray<CObArray,CMyFactory*> CMyFactoryArray;

#endif/*__CMYFACTORY_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

