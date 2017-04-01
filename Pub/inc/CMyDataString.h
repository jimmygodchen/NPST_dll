//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATASTRING_H
#define __CMYDATASTRING_H

//---------------------------------------------- CMyDataString ----------------------
class CLASS_EXPORT CMyDataString:public CMyData
{
public:
    DECLARE_SERIAL(CMyDataString);
    CMyDataString();

public:
    CString m_strValue;

public:
    virtual void RefreshData(CString str);
};


#endif/*__CMYDATASTRING_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

