
// 0202-1Dlg.h : header file
//

#pragma once


// CMy02021Dlg dialog
class CMy02021Dlg : public CDialogEx
{
// Construction
public:
	CMy02021Dlg(CWnd* pParent = NULL);	// standard constructor
	~CMy02021Dlg();

// Dialog Data
	enum { IDD = IDD_MY02021_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	static ULONG_PTR m_gdiplusToken;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	/**
	 * function: 增减文字到图像上
	 * param:
	 * return: 
	*/
	void AddTextToImage();

	void AddTextToImage(LPCTSTR lpszImagePath, LPCTSTR lpszText, LPCTSTR lpszImagePathSave);

	/** 
	 * name    GetEncoderClsid 
	 * brief   取图片类型GLSID 
	 * param[in]        const WCHAR * format 
	 * param[in]        CLSID * pClsid 
	 * return           int 
	*/
	int GetEncoderClsid(const TCHAR* format, CLSID* pClsid);

	void test_GetEncoderClsid();
};
