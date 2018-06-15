// ImageTextDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "ImageText.h"
#include "ImageTextDlg.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageTextDlg dialog

CImageTextDlg::CImageTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageTextDlg)
	m_OriginX = 0;
	m_OriginY = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	GdiplusStartup(&m_pGdiToken, &m_Gdiplus, NULL);		//初始化GDI+
	m_pBmp = NULL;
}

void CImageTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageTextDlg)
	DDX_Control(pDX, IDC_IMAGEDEMO, m_ImageDemo);
	DDX_Control(pDX, IDC_WATERMARK, m_WaterText);
	DDX_Control(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_ORIGINX, m_OriginX);
	DDX_Text(pDX, IDC_ORIGINY, m_OriginY);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageTextDlg, CDialog)
	//{{AFX_MSG_MAP(CImageTextDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_IMAGE_TEXT, OnImageText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageTextDlg message handlers

BOOL CImageTextDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageTextDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageTextDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CImageTextDlg::OnBrowse() 
{
	CFileDialog flDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"图像文件|*.bmp;*.jpg;*.jpeg;*.gif||");					//定义文件打开对话框
	if (flDlg.DoModal() == IDOK)
	{
		CString szText = flDlg.GetPathName();
		m_FileName.SetWindowText(szText);
		if (m_pBmp != NULL)
		{
			delete m_pBmp;
			m_pBmp = NULL;
		}
		m_pBmp = Bitmap::FromFile(szText.AllocSysString());
		Color bkClr(0, 0, 0);
		HBITMAP hBmp;
		m_pBmp->GetHBITMAP(bkClr, &hBmp);
		m_ImageDemo.SetBitmap(hBmp);
		szText.ReleaseBuffer();
	}
}
//水印处理
void CImageTextDlg::OnImageText() 
{
	UpdateData();
	CString szText;
	m_WaterText.GetWindowText(szText);
	if (!szText.IsEmpty() && m_pBmp != NULL)
	{
		Graphics *pGraph = Graphics::FromImage(m_pBmp);
		Brush *brush = new SolidBrush (Color(255, 0, 0, 0));
		Font *font = new Font(L"Arial", 12);
		PointF ptf;
		ptf.X = m_OriginX;
		ptf.Y = m_OriginY;
		//确定字符长度
		int nLen = MultiByteToWideChar(CP_ACP, 0, szText, -1, NULL, 0);
		//在位图中输出字符串
		pGraph->DrawString(szText.AllocSysString(), nLen, font, ptf, brush);
		szText.ReleaseBuffer();
		Color clr;
		HBITMAP hBmp, hOldBmp;
		m_pBmp->GetHBITMAP(clr, &hBmp);
		hOldBmp = m_ImageDemo.SetBitmap(hBmp);
		if (hOldBmp)
		{
			DeleteObject(hOldBmp);
		}
	}
}
