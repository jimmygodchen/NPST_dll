; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=6
ResourceCount=6
NewFileInclude1=#include "stdafx.h"
Class1=CMyNPS7510Dlg
LastClass=CMyDlgRegulate
LastTemplate=CDialog
Resource1=IDD_DLG_SETPOINT
Class2=CMyDlgParam
Resource2=IDD_DLG_PARAM
Class3=CMyDlgRegulate
Resource3=IDD_UNIT_NPS7510
Class4=CMyDlgSetpoint
Resource4=IDD_DLG_REGULATE
Class5=CMyDlgYC
Resource5=IDD_DLG_YC
Class6=CMyOpenList
Resource6=IDD_DLG_OPLIST

[DLG:IDD_UNIT_NPS7510]
Type=1
Class=CMyNPS7510Dlg
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_ADDR,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_TIMEOUT,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:CMyNPS7510Dlg]
Type=0
HeaderFile=CMyNPS7510Dlg.h
ImplementationFile=CMyNPS7510Dlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_EDIT_ADDR
VirtualFilter=idWC

[DLG:IDD_DLG_PARAM]
Type=1
Class=CMyDlgParam
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_PARAM,static,1073741831

[CLS:CMyDlgParam]
Type=0
HeaderFile=CMyDlgParam.h
ImplementationFile=CMyDlgParam.cpp
BaseClass=CBCGPDialog
Filter=D
LastObject=CMyDlgParam
VirtualFilter=dWC

[DLG:IDD_DLG_REGULATE]
Type=1
Class=CMyDlgRegulate
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_PARAM,static,1073741831

[CLS:CMyDlgRegulate]
Type=0
HeaderFile=CMyDlgRegulate.h
ImplementationFile=CMyDlgRegulate.cpp
BaseClass=CBCGPDialog
Filter=D
LastObject=CMyDlgRegulate
VirtualFilter=dWC

[DLG:IDD_DLG_SETPOINT]
Type=1
Class=CMyDlgSetpoint
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_PARAM,static,1073741831

[CLS:CMyDlgSetpoint]
Type=0
HeaderFile=CMyDlgSetpoint.h
ImplementationFile=CMyDlgSetpoint.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMyDlgSetpoint

[DLG:IDD_DLG_YC]
Type=1
Class=CMyDlgYC
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BTN_H,button,1342242816
Control4=IDC_BTN_F,button,1342242816

[CLS:CMyDlgYC]
Type=0
HeaderFile=CMyDlgYC.h
ImplementationFile=CMyDlgYC.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMyDlgYC

[DLG:IDD_DLG_OPLIST]
Type=1
Class=CMyOpenList
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_PARAM,static,1073741831
Control4=IDC_BUTTON_REFRESH,button,1342242817

[CLS:CMyOpenList]
Type=0
HeaderFile=CMyOpenList.h
ImplementationFile=CMyOpenList.cpp
BaseClass=CBCGPDialog
Filter=D
LastObject=CMyOpenList
VirtualFilter=dWC

