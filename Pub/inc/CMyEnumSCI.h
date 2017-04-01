/*
;*****************************************************************************************************
;*						Copyright (c) 2009 by ThinkBoy. 
;*						All rights reserved.
;*
;* Header:
;* File Name: 
;* Author: jimmy
;* Date:
;*****************************************************************************************************
;*/

#ifndef __CMYENUMSCI_H
#define __CMYENUMSCI_H

class CLASS_EXPORT CMyEnumSCI
{
public:
//     CStringArray m_arKey;
    static CStringArray m_arCOM;

protected:
    static BOOL m_bInited;

public:
    static void EnumSCI(void);
    static int GetSCIID(int nIndex);
};

#endif /*__CMYENUMSCI_H*/

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/