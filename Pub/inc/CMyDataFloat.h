//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAFLOAT_H
#define __CMYDATAFLOAT_H

//---------------------------------------------- CMyDataFloat -----------------
class CLASS_EXPORT CMyDataFloat:public CMyData
{
public:
    DECLARE_SERIAL(CMyDataFloat);
    CMyDataFloat();

public:
    CString m_strUnitage;           // 数据单位(如"kV","kA","Hz"等);
    BYTE m_Format;                  // 数据格式(如0:"%.0f",2:"%.2f"等);
    float m_fData;                  // 当前运行值;

public:
    virtual void Initialize(CString strName, CString strUnitage, BYTE Format);

public:
    virtual void RefreshData(float fData);

};

#endif/*__CMYDATAFLOAT_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

