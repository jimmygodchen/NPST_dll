//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAVIEW_H
#define __CMYDATAVIEW_H

//---------------------------------------------- CMyDataView ----------------------
class CLASS_EXPORT CMyDataView:public CMyObj
{
public:
    static CPtrArray s_aClass;
    static void RegisterClass(CRuntimeClass* pRuntimeClass);

public:
    DECLARE_SERIAL(CMyDataView);
    CMyDataView();
    ~CMyDataView();

public:
    virtual void OnViewData(void){};
};

#endif/*__CMYDATAVIEW_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

