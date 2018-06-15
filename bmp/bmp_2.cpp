	//BOOL StretchBlt(
	//int x,				// 指定目的矩形区域左上角的X坐标
	//int y,				// 指定目的矩形区域左上角的Y坐标
	//int nWidth,			// 指定目的矩形区域的宽度
	//int nHeight,			// 指定目的矩形区域的高度
	//CDC* pSrcDC,			// 源设备场景(设备上下文)
	//int xSrc,				// 指定源矩形区域左上角的X坐标
	//int ySrc,				// 指定源矩形区域左上角的Y坐标
	//int nSrcWidth,		// 指定源矩形区域的宽度
	//int nSrcHeight,		// 指定源矩形区域的高度
	//DWORD dwRop			// 此参数参考MSDN，SRCCOPY类型为直接拷贝
	//);					//此函数将一个位图资源从一个矩形区域拷贝到另一个矩形区域，即缩放位图 

	//BOOL TransparentBlt(
	//int xDest,
	//int yDest,
	//int nDestWidth,
	//int nDestHeight,
	//CDC* pSrcDC,
	//int xSrc,
	//int ySrc,
	//int nSrcWidth,
	//int nSrcHeight,
	//UINT clrTransparent 
	//);					//此函数同样具有缩放功能，但此函数最后一个参数用来指定作为透明色的RGB；

	//BOOL BitBlt(
	//int x,
	//int y,
	//int nWidth,
	//int nHeight,
	//CDC* pSrcDC,
	//int xSrc,
	//int ySrc,
	//DWORD dwRop 
	//);					//此函数同样用来拷贝位图资源，但不具备缩放功能.
	
	CBitmap BackBmp;
	BackBmp.LoadBitmapW(IDB_BITMAP1);
	BITMAP bm;
	BackBmp.GetBitmap(&bm);		// 获取位图结构信息

	CDC ImageDC;
	ImageDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = ImageDC.SelectObject(&BackBmp);

	// dc表示的设备上下文为目标DC,
	pDC->StretchBlt(0, 0, bm.bmWidth + 15, bm.bmHeight + 15, &ImageDC,
		0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	/*ImageDC.SelectObject(pOldBmp);
	CBitmap ForeBmp;
	ForeBmp.LoadBitmapW(IDB_BITMAP2);
	ForeBmp.GetBitmap(&bm);
	pOldBmp = ImageDC.SelectObject(&ForeBmp);
	pDC->TransparentBlt(0, 0, bm.bmWidth + 15, bm.bmHeight + 15, &ImageDC,
		0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));*/

	ImageDC.SelectObject(pOldBmp);
	ImageDC.DeleteDC();