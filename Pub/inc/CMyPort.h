//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYPORT_H
#define __CMYPORT_H

#define COMBUFFSIZE           16000

#define WM_PORTMSG            (WM_USER + 1)             // 端口报文消息

typedef struct
{
//     CString strPortName;
    COLORREF clrColor;
    CString strContent;
}PORTMSG;

//---------------------------------------------- CMyPort ----------------------
class CLASS_EXPORT CMyPort:public CMyObj
{
public:
    static CStringArray s_aType;
    static CMapStringToPtr s_mapTypeToClass;
    static void RegisterClass(CString strType, CRuntimeClass* pRuntimeClass);

public:
    DECLARE_SERIAL(CMyPort);
    CMyPort();
    virtual ~CMyPort();

public:
    CPtrArray m_aMsg;                   // 通讯报文
    CMyUnitArray m_aUnit;				// 下挂的所有单元;
    WORD m_wDelayWriteCom;				// 发送前延时毫秒数;
    BOOL m_bAutoSndMsg;                 // 调用ReadCom和Write时自动发送报文消息
    CWnd* m_pwndMsg;                     // 接收消息的窗口

public:
    int m_nComUnitNo;					// 当前通信处理单元;
    CMyWorkThread* m_pWorkThread;		// 通信工作线程;
// protected:
//     BOOL m_bRequestSyn;					// 通信校时标志;
//     WORD m_wSynDiff;					// 校时修正值(毫秒);
// public:
//     BOOL m_bComReport;					// 报文监测标志;
//     short* m_pComReportHead;			// 报文监测缓冲区头;
//     short* m_pComReportTail;			// 报文监测缓冲区尾;
//     short* m_pComReportCur;				// 报文监测当前指针;
//     CDialog* m_pComReportDlg;			// 报文监测窗口;
// public:
//     virtual BOOL OnAttrib(CPropertySheet& sheet);
//     virtual void Serialize(CArchive& ar);
//     virtual void GetParamHead(CStringArray& aParamHead);
//     virtual void GetParamInfo(CStringArray& aParamInfo);
// public:
//     virtual void OnTimerFast(void);
//     virtual void OnTimer1Sec(void);
//     virtual void OnTimer5Sec(void);
//     virtual void OnTimer1Min(void);
//     virtual void OnTimer1Hour(void);
public:
//     virtual void OnComGotoStandby(void){};
    virtual BOOL OpenCom(void){ return FALSE; };
    virtual void CloseCom(void){};
    virtual void ClearCom(void){};
    virtual int ReadCom(BYTE* pRXData,int nRXLength){ return 0; };
    virtual int WriteCom(BYTE* pTXData,int nTXLength){ return 0; };

public:
//     void TriggerSyn(void);
    void StartComLoop(void);
    void StopComLoop(void);
    void ComLoop(void);
//     void StartComReport(void);
//     void StopComReport(void);
//     void ToggleComReportDlg(void);
//     void AddComReportRX(BYTE* pData,int nCount);
//     void AddComReportTX(BYTE* pData,int nCount);
// protected:
//     void BeginReadCom(void);
//     void EndReadCom(void);
//     void BeginWriteCom(void);
//     void EndWriteCom(void);

public:
    void AddComReportRX(BYTE* pData,int nCount);
    void AddComReportTX(BYTE* pData,int nCount);
    void SndMsg(const PORTMSG& PortMsg);
    BOOL GetMsg(PORTMSG& PortMsg);
};

typedef CTypedPtrList<CObList,CMyPort*> CMyPortList;
typedef CTypedPtrArray<CObArray,CMyPort*> CMyPortArray;

#endif/*__CMYPORT_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

