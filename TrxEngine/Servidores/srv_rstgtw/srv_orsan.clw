; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSrv_orsanDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "srv_orsan.h"

ClassCount=4
Class1=CSrv_orsanApp
Class2=CSrv_orsanDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SRV_ORSAN_DIALOG
Resource4=IDD_ABOUTBOX (Spanish (Modern))
Class4=COrsanSocket
Resource5=IDD_SRV_ORSAN_DIALOG (Spanish (Modern))

[CLS:CSrv_orsanApp]
Type=0
HeaderFile=srv_orsan.h
ImplementationFile=srv_orsan.cpp
Filter=N

[CLS:CSrv_orsanDlg]
Type=0
HeaderFile=srv_orsanDlg.h
ImplementationFile=srv_orsanDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_DELAY

[CLS:CAboutDlg]
Type=0
HeaderFile=srv_orsanDlg.h
ImplementationFile=srv_orsanDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_SRV_ORSAN_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSrv_orsanDlg

[DLG:IDD_SRV_ORSAN_DIALOG (Spanish (Modern))]
Type=1
Class=CSrv_orsanDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_CONNECT,button,1342242816
Control4=IDC_BUTTON_SEND,button,1342242816
Control5=IDC_BUTTON_CLOSE,button,1342242816
Control6=IDC_LIST_TRACE,listbox,1353781505
Control7=IDC_BUTTON_CLEAR,button,1342242816
Control8=IDC_BUTTON_INYECTA_TRANSACCION,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_DELAY,edit,1350631552

[DLG:IDD_ABOUTBOX (Spanish (Modern))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:COrsanSocket]
Type=0
HeaderFile=OrsanSocket.h
ImplementationFile=OrsanSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

