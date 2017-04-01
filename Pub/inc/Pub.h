//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __PUB_H
#define __PUB_H

#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxmt.h>
// #include <afxsock.h>
#include <afxtempl.h>
#include <afxcview.h>
#include <io.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <conio.h>
#include <direct.h>
#include <mmsystem.h>
#include <vfw.h>
#include <BCGCBProInc.h>			// BCGControlBar Pro

extern AFX_EXTENSION_MODULE PublicDLL;

#ifdef _PUBLIC_IMPL
#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

//---------------------------------------------- CMyCRC8 ----------------------
class CLASS_EXPORT CMyCRC8
{
protected:
    BYTE m_Table[256];
    BOOL m_bInvert;
    
public:
    CMyCRC8(BYTE Poly,BOOL bInvert);
    void CalculateCRC(BYTE* pData,int nLength,BYTE& CRC);
};


//---------------------------------------------- CMyCRC16 ---------------------
class CLASS_EXPORT CMyCRC16
{
protected:
    WORD m_wTable[256];
    BOOL m_bInvert;
    
public:
    CMyCRC16(WORD wPoly,BOOL bInvert);
    void CalculateCRC(BYTE* pData,int nLength,WORD& wCRC);
};

//---------------------------------------------- CMyCommDispatch --------------
typedef struct
{
    DWORD dwTaskSpan100ms;
    DWORD dwTaskClock100ms;
}tTASK;

class CLASS_EXPORT CMyCommDispatch
{
protected:
    CArray<tTASK, tTASK&> m_aTask;

public:
    CMyCommDispatch();

public:
    void AddTask(DWORD dwSpan100ms);
    void ResetTask(int nTaskNo);
    int GetActiveTask(BOOL bResetAuto = TRUE);
};


//---------------------------------------------- CMyWorkThread ----------------
enum THREADFLAG
{
    TF_NULL,
    TF_RUNNING,
    TF_EXITING,
};

class CLASS_EXPORT CMyWorkThread
{
public:
    static CPtrArray s_aWorkThread;
    
public:
    CMyWorkThread();
    ~CMyWorkThread();
    
public:
    LPVOID m_pParam;
    CEvent m_eventExit;
    THREADFLAG m_nThreadFlag;
    CWinThread* m_pWinThread;
    
public:
    inline void InternalReset(void){ m_nThreadFlag = TF_NULL; };
    inline void InternalRun(void){ m_nThreadFlag = TF_RUNNING; };
    inline void InternalExit(void){ m_nThreadFlag = TF_EXITING; };
    inline BOOL InternalIsRunning(void){ return (m_nThreadFlag==TF_RUNNING); };
    inline BOOL InternalIsExiting(void){ return (m_nThreadFlag==TF_EXITING); };
    
public:
    void Run(AFX_THREADPROC pfnThreadProc,LPVOID pParam,int nPriority);
    void Exit(void);
};

//---------------------------------------------------------------------------------------------
#include "CMyObj.h"
#include "CMyData.h"
#include "CMyDataFloat.h"
#include "CMyDataBin.h"
#include "CMyDataString.h"
#include "CMyVector.h"
#include "CMyDataVector.h"
#include "CMyDataOperate.h"
#include "CMyDataMem.h"
#include "CMyRTWave.h"
#include "CMyFactory.h"
#include "CMyUnit.h"
#include "CMyPort.h"
#include "CMyPortMng.h"
#include "CMyEnumSCI.h"
#include "CMyDataView.h"
#include "CMyEventMng.h"
#include "CMyWaveInfo.h"

typedef struct
{
    CString strDeviceType;
    CString strOEMType;
}tMAPDEVICETYPE;

typedef CArray<tMAPDEVICETYPE, tMAPDEVICETYPE&> CMyMapDeviceTypeArray;

typedef CArray<CFileStatus,CFileStatus&> CFileStatusArray;

extern CLASS_EXPORT void MySystemCreate(void);
extern CLASS_EXPORT void MySystemDestroy(void);
extern CLASS_EXPORT void MyLoadDllInfo(void);           // 加载动态库信息
extern CLASS_EXPORT void MyLoadAllLibrary(void);        // 加载动态库
extern CLASS_EXPORT void MyFreeAllLibrary(void);

extern CLASS_EXPORT int MyDoModal(CDialog* pDlg,HINSTANCE hInstance);
extern CLASS_EXPORT int MyMessageBox(CString strMessage,CString strTitle,UINT uType);
extern CLASS_EXPORT CString MyReverseSpanExcluding(CString strSource,CString strSpan);
extern CLASS_EXPORT void MyAbortSystem(CString strMessage);

// extern CLASS_EXPORT void ReadConfig(CString strFileName);
// extern CLASS_EXPORT void WriteConfig(CString strFileName);

extern CLASS_EXPORT void InitMapDeviceType(void);
extern CLASS_EXPORT BOOL DeviceType2OEMType(CString strDeviceType, CString& strOEMType);

extern CLASS_EXPORT CString g_strSysPath;
extern CLASS_EXPORT CFileStatusArray g_aDllInfo;        // 动态连接库文件状态;

extern CLASS_EXPORT CMyPortMng g_MngPort;
extern CLASS_EXPORT CMyDataView* g_pDataView;
extern CLASS_EXPORT CMyEventMng g_MngEvent;

extern CLASS_EXPORT CMyMapDeviceTypeArray g_aMapDeviceType;

#endif/*__PUB_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

