void CMy04181View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// Do not call CFormView::OnPaint() for painting messages

	TCHAR szCurrPath[MAX_PATH] = {0};
	GetCurrentDirectory(MAX_PATH, szCurrPath);
	if(szCurrPath[_tcslen(szCurrPath)] != '\\')
		szCurrPath[_tcslen(szCurrPath)] = _T('\\');
	CString strImgPath = szCurrPath;
	strImgPath += _T("test.bmp");

	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, strImgPath, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
	if(NULL == hBmp)
		return ;

	CBitmap bmp;
	bmp.Attach(hBmp);	// 关联位图

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	BITMAP bitmap;	// 定义位图结构，将图片信息保存在位图结构体重
	bmp.GetBitmap(&bitmap);

	CBitmap* pOldBmp = NULL;
	memDC.SelectObject(&bmp);

	// 获取客户区的宽高
	CRect rc;
	GetClientRect(&rc);

	// 显示图片
	// CDC::BitBlt不会对原来的位图进行拉伸或压缩，只会根据我们给定的
	// nWidth, nHeight值来决定改有多少部分进行显示
	//dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);

	// #define STRETCH_ANDSCANS    BLACKONWHITE  
	// #define STRETCH_ORSCANS     WHITEONBLACK  
	// #define STRETCH_DELETESCANS COLORONCOLOR  
	// #define STRETCH_HALFTONE    HALFTONE  
	
	// 如果希望图片和矩形区域能自动适应，可以用下面的函数
	// StretchBlt会造成图像的失真，可以调用下面的这个函数设置
	SetStretchBltMode(dc.m_hDC,STRETCH_HALFTONE);	// 效果最好,最慢
	// SetStretchBltMode(dc.m_hDC,COLORONCOLOR); 
	// SetStretchBltMode(dc.m_hDC,WHITEONBLACK); 
	// SetStretchBltMode(dc.m_hDC,BLACKONWHITE); 
	
	dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &memDC, 
		0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	// 恢复工作
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();