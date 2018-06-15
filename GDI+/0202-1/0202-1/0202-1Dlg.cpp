
// 0202-1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "0202-1.h"
#include "0202-1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONG_PTR CMy02021Dlg::m_gdiplusToken = NULL;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CMy02021Dlg::CMy02021Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy02021Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMy02021Dlg::~CMy02021Dlg()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

void CMy02021Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy02021Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMy02021Dlg message handlers

BOOL CMy02021Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	// test_GetEncoderClsid();
	// AddTextToImage(_T("test.bmp"), _T("testasdfasdfasdfasdfasdfasdfasdfasdfasdfadfasdf"), _T("test_save.bmp"));
	AddTextToImage();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy02021Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy02021Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy02021Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy02021Dlg::AddTextToImage()
{
	TCHAR szImgPath[] = _T("1.png");
	TCHAR szSaveName[] = _T("test_save.png");
	// 加载图片
	Image img(szImgPath);
	// //通过Image对象创建一个绘图句柄，使用这个句柄对图片进行操作 
	Graphics imgGraphics(&img);

	imgGraphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	TCHAR szText[] = _T("asdf");
	FontFamily fontFamily(_T("楷体"));
	// 10表示字体大小
	Gdiplus::Font myFont(&fontFamily, 10, FontStyleRegular, UnitPoint);
	SolidBrush blackBrush(Color(255, 0, 0, 0));		// 半透明+文字RGB颜色
	PointF school_site((REAL)50, (REAL)50);		// 文字放置的像素坐标
	StringFormat format;
	format.SetAlignment(StringAlignmentNear);		//文本排列方式，即在对应位置居中、靠左、靠右
	imgGraphics.DrawString(szText, _tcslen(szText), &myFont, school_site, &format, &blackBrush);

	CLSID Clsid;
	GetEncoderClsid(_T("image/png"), &Clsid);
	img.Save(szSaveName, &Clsid, NULL);
}

int CMy02021Dlg::GetEncoderClsid(const TCHAR* format, CLSID* pClsid)
{
	UINT num = 0;
	UINT size = 0;
	ImageCodecInfo *pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (0 == size)
		return -1;

	pImageCodecInfo = (ImageCodecInfo *)malloc(size);
	if (NULL == pImageCodecInfo)
		return -2;

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT i = 0; i < num; ++i)
	{
		if (_tcscmp(pImageCodecInfo[i].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[i].Clsid;
			free(pImageCodecInfo);
			return i;
		}
	}

	free(pImageCodecInfo);
	return -3;
}

void CMy02021Dlg::test_GetEncoderClsid()
{
	CLSID encoderClsid;
	GetEncoderClsid(_T("image/jpeg"), &encoderClsid);
	GetEncoderClsid(_T("image/png"), &encoderClsid);
	GetEncoderClsid(_T("image/bmp"), &encoderClsid);
	GetEncoderClsid(_T("image/gif"), &encoderClsid);
	GetEncoderClsid(_T("image/tiff"), &encoderClsid);
}

void CMy02021Dlg::AddTextToImage(LPCTSTR lpszImagePath, LPCTSTR lpszText, LPCTSTR lpszImagePathSave)
{
	// 加载图片
	Image img(lpszImagePath);
	// //通过Image对象创建一个绘图句柄，使用这个句柄对图片进行操作 
	Graphics imgGraphics(&img);

	imgGraphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	FontFamily fontFamily(_T("楷体"));
	// 10表示字体大小
	Gdiplus::Font myFont(&fontFamily, 10, FontStyleRegular, UnitPoint);
	SolidBrush blackBrush(Color(255, 255, 0, 0));		// 半透明+文字RGB颜色
	PointF school_site((REAL)0, (REAL)0);		// 文字放置的像素坐标
	StringFormat format;
	format.SetAlignment(StringAlignmentNear);		//文本排列方式，即在对应位置居中、靠左、靠右
	imgGraphics.DrawString(lpszText, _tcslen(lpszText), &myFont, school_site, &format, &blackBrush);

	CLSID Clsid;
	CString strImgPath(lpszImagePath);
	CString strFormat(_T("image/"));
	CString strSuffix = strImgPath.Right(strImgPath.GetLength() - strImgPath.ReverseFind(_T('.')) - 1);
	if (strSuffix == CString(_T("jpg")) || strSuffix == CString(_T("jpeg")))
		strFormat = strFormat + _T("jpeg");
	else
		strFormat = strFormat + strSuffix;
	GetEncoderClsid(strFormat, &Clsid);
	img.Save(lpszImagePathSave, &Clsid, NULL);
}

