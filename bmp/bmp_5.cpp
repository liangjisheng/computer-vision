void CMy04192View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// Do not call CFormView::OnPaint() for painting messages

	// 资源可以用一个整数来标示，也可以用一个字符串标示。但无论如何，这些ID都不是指位图文件名。不要将它们混淆。
	// LoadBitmap的参数不论那种类型都是针对资源而言，CBitmap是不提供直接从文件中读取位图的功能的！
	CBitmap bmp;

	// 使用字符串表示资源
	bmp.LoadBitmap(_T("bitmap1"));
	if(NULL == bmp.m_hObject)
	{
		AfxMessageBox(_T("load bitmap failed."));
		return ;
	}

	// 使用整数来表示资源，加载位图
	//bmp.LoadBitmap(IDB_BITMAP1);
	CDC  memdc;
	BITMAP bmstru;
	bmp.GetBitmap(&bmstru);
	memdc.CreateCompatibleDC(&dc);
	CBitmap* pOldBmp = memdc.SelectObject(&bmp);
	dc.BitBlt(0,0,bmstru.bmWidth,bmstru.bmHeight,&memdc,0,0,SRCCOPY);

	memdc.SelectObject(pOldBmp);
	memdc.DeleteDC();
	bmp.DeleteObject();
}