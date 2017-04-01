; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=5
ResourceCount=5
NewFileInclude1=#include "stdafx.h"
Class1=CMyDlgUnitParam
LastClass=CMyDlgOpList
LastTemplate=CDialog
Resource1=IDD_UNIT_PARAM
Class2=CMyDlgParam
Resource2=IDD_DLG_PARAM
Class3=CMyDlgRegulate
Resource3=IDD_DLG_SETPOINT
Class4=CMyDlgSetpoint
Resource4=IDD_DLG_REGULATE
Class5=CMyDlgOpList
Resource5=IDD_DLG_OPLIST

[DLG:IDD_UNIT_PARAM]
Type=1
Class=CMyDlgUnitParam
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_ADDR,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_TIMEOUT,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:CMyDlgUnitParam]
Type=0
HeaderFile=CMyDlgUnitParam.h
ImplementationFile=CMyDlgUnitParam.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CMyDlgUnitParam

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
BaseClass=CDialog
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
BaseClass=CBCGPDialog
Filter=D
LastObject=CMyDlgSetpoint
VirtualFilter=dWC

[DLG:IDD_DLG_OPLIST]
Type=1
Class=CMyDlgOpList
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_PARAM,static,1073741831
Control4=IDC_BUTTON_REFRESH,button,1342242817

[CLS:CMyDlgOpList]
Type=0
HeaderFile=CMyDlgOpList.h
ImplementationFile=CMyDlgOpList.cpp
BaseClass=CDialog
Filter=D
LastObject=CMyDlgOpList
VirtualFilter=dWC

