//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYPORTMNG_H
#define __CMYPORTMNG_H

//---------------------------------------------- CMyPortMng ----------------------
class CLASS_EXPORT CMyPortMng:public CMyObj
{
public:
    DECLARE_SERIAL(CMyPortMng);
    CMyPortMng();
    ~CMyPortMng();

public:
    CMyPort* m_pPort;

public:
    void OpenAllPorts(void);
    void CloseAllPorts(void);
    CMyPort* GetPort(int nPortID);

};

#endif/*__CMYPORTMNG_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

