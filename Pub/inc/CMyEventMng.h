//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYEVENTMNG_H
#define __CMYEVENTMNG_H

#define WM_EVENTMSG            (WM_USER + 2)             // 事件消息

typedef struct
{
    WORD wYear;                     // 年
    BYTE Mon;                       // 月
    BYTE Day;                       // 日
    BYTE Hour;                      // 时
    BYTE Min;                       // 分
    BYTE Sec;                       // 秒
    WORD wMs;                       // 毫秒
    COLORREF clrColor;              // 颜色
    CString strContent;             // 内容
}EVTMSG;

typedef CArray<EVTMSG, EVTMSG&> CMyEventArray;

class CLASS_EXPORT CMyEventMng:public CMyObj
{
public:
    DECLARE_SERIAL(CMyEventMng);
    CMyEventMng();
    ~CMyEventMng();

public:
    CWnd* m_pwndMsg;                    // 接收消息的窗口
    CMyEventArray m_aEvent;             // 事件

public:
    void SndMsg(const EVTMSG& EventMsg);
    BOOL GetMsg(EVTMSG& EventMsg);
    void Empty(void);
};


#endif/*__CMYEVENTMNG_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

