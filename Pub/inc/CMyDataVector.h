//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAVECTOR_H
#define __CMYDATAVECTOR_H

//---------------------------------------------- CMyDataVector -----------------
class CLASS_EXPORT CMyDataVector:public CMyDataFloat
{
public:
    DECLARE_SERIAL(CMyDataVector);
    CMyDataVector();

public:
//     CString m_strUnitage;           // 数据单位(如"kV","kA","Hz"等);
//     BYTE m_Format;                  // 数据格式(如0:"%.0f",2:"%.2f"等);
//     float m_fData;                  // 当前运行值;
    CMyVector m_vec;
    int m_nDisplayType;                 // 显示方式: 0 - R+jX, 1 - A∠
    BYTE m_AngFormat;

public:
    virtual void Initialize(CString strName, CString strUnitage, BYTE Format, BYTE AngFormat = 0, int nDisplayType = 0);

public:
    virtual void RefreshData(CMyVector Vec);
};

#endif/*__CMYDATAVECTOR_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

