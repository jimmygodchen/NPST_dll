//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATABIN_H
#define __CMYDATABIN_H

//---------------------------------------------- CMyDataBin ----------------
class CLASS_EXPORT CMyDataBin:public CMyData
{
public:
    DECLARE_SERIAL(CMyDataBin);
    CMyDataBin();

public:
    BYTE m_Status;                              // µ±Ç°×´Ì¬;

// public:
//     virtual void Initialize(CString strName);

public:
    virtual void RefreshData(BYTE Status);

};



#endif/*__CMYDATABIN_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

