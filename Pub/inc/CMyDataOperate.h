//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAOPERATE_H
#define __CMYDATAOPERATE_H

//---------------------------------------------- CMyDataOperate ---------------
class CLASS_EXPORT CMyDataOperate:public CMyData
{
public:
    DECLARE_SERIAL(CMyDataOperate);
    CMyDataOperate();

protected:
    BYTE m_OperateCode;

public:
    inline BYTE GetOperateCode(void){ return m_OperateCode; };
    virtual BOOL ExeOperate(void);
    virtual void EndOperate(void);
    virtual void SetOperateCode(BYTE OperateCode=0xff);

};



#endif/*__CMYDATAOPERATE_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

