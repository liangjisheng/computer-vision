; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImageTextDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ImageText.h"

ClassCount=3
Class1=CImageTextApp
Class2=CImageTextDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_IMAGETEXT_DIALOG

[CLS:CImageTextApp]
Type=0
HeaderFile=ImageText.h
ImplementationFile=ImageText.cpp
Filter=N

[CLS:CImageTextDlg]
Type=0
HeaderFile=ImageTextDlg.h
ImplementationFile=ImageTextDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BROWSE

[CLS:CAboutDlg]
Type=0
HeaderFile=ImageTextDlg.h
ImplementationFile=ImageTextDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IMAGETEXT_DIALOG]
Type=1
Class=CImageTextDlg
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FILENAME,edit,1350631552
Control3=IDC_BROWSE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ORIGINX,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ORIGINY,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_WATERMARK,edit,1350631552
Control10=IDC_IMAGE_TEXT,button,1342242816
Control11=IDC_IMAGEDEMO,static,1342177294

