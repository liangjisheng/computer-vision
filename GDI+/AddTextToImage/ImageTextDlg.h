//Download by http://www.NewXing.com
// ImageTextDlg.h : header file
//

#if !defined(AFX_IMAGETEXTDLG_H__78E8CF82_1AB7_418E_A4A2_E99EF0B0285C__INCLUDED_)
#define AFX_IMAGETEXTDLG_H__78E8CF82_1AB7_418E_A4A2_E99EF0B0285C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImageTextDlg dialog

#include "Gdiplus//Gdiplus.h"					//引用头文件	
using namespace Gdiplus;						//引用命名空间
#pragma comment (lib,"Gdiplus//gdiplus.lib")	//引用库文件



class CImageTextDlg : public CDialog
{
// Construction
public:
	CImageTextDlg(CWnd* pParent = NULL);	// standard constructor
	GdiplusStartupInput m_Gdiplus;			//定义GDI+初始化变量
	ULONG_PTR m_pGdiToken;				//定义GID+标识
	Bitmap *m_pBmp;						//定义位图对象，派生于Image类

// Dialog Data
	//{{AFX_DATA(CImageTextDlg)
	enum { IDD = IDD_IMAGETEXT_DIALOG };
	CStatic	m_ImageDemo;
	CEdit	m_WaterText;
	CEdit	m_FileName;
	UINT	m_OriginX;
	UINT	m_OriginY;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnImageText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGETEXTDLG_H__78E8CF82_1AB7_418E_A4A2_E99EF0B0285C__INCLUDED_)
