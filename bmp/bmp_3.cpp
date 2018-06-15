void CMy04191View::CreateStretchImage(CImage *pImage,CImage *ResultImage, int StretchWidth, int StretchHeight)
{
	if(pImage->IsDIBSection())
	{
		// 取得 pImage 的 DC
		// Image 因为有自己的 DC, 所以必須使用 FromHandle 取得对应的 DC
		CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC());
		CBitmap *bitmap1=pImageDC1->GetCurrentBitmap();
		BITMAP bmpInfo;
		bitmap1->GetBitmap(&bmpInfo);

		// 建立新的 CImage
		ResultImage->Create(StretchWidth, StretchHeight, bmpInfo.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());

		// 当Destination 较小的时候, 会根据 Destination DC 上的 Stretch Blt mode 決定是否要保留被删除点的资讯
		ResultImageDC->SetStretchBltMode(HALFTONE); // 使用最高品质的方式
		::SetBrushOrgEx(ResultImageDC->m_hDC,0,0,NULL); // 调整 Brush 的原点

		// 把 pImage 画到 ResultImage 上面
		StretchBlt(*ResultImageDC, 0, 0, StretchWidth, StretchHeight, *pImageDC1, 
			0, 0, pImage->GetWidth(), pImage->GetHeight(), SRCCOPY);
		// pImage->Draw(*ResultImageDC,0,0,StretchWidth,StretchHeight,0,0,pImage->GetWidth(),pImage->GetHeight());

		pImage->ReleaseDC();
		ResultImage->ReleaseDC();
	}
}


void CMy04191View::reateStretchBmp(CBitmap* pBitmap, int StretchWidth, int StretchHeight, CBitmap *pResultBmp)
{
	// 建立显示屏幕的DC
	CDC dcScreen;
	dcScreen.Attach(::GetDC(NULL));
	// 取得原始图像的dc
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dcScreen);
	CBitmap *pOldOrgBitmap= dcMemory.SelectObject(pBitmap);

	// 建立新的結果图像 (指定大小)
	pResultBmp->CreateCompatibleBitmap(&dcScreen,StretchWidth,StretchHeight);

	// 取得結果图像的 dc
	CDC dcFixMemory;
	dcFixMemory.CreateCompatibleDC(&dcScreen);
	// 让 dcFixMemory 选择到 "結果bmp", 任何对 dcFixMemory 的动作都会反映到 pResultBmp
	CBitmap *pOldReslutBitmap=dcFixMemory.SelectObject(pResultBmp); 

	// 把原始图像缩放画到 Memory DC上面
	BITMAP bmpInfo;
	pBitmap->GetBitmap(&bmpInfo); // 取得原始图像的宽度与高度
	StretchBlt(dcFixMemory, 0, 0, StretchWidth, StretchHeight, dcMemory,
		0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	// Set Back
	dcMemory.SelectObject(pOldOrgBitmap);
	dcFixMemory.SelectObject(pOldReslutBitmap);
}


unsigned char* CMy04191View::do_Stretch_Linear(int w_Dest,int h_Dest,int bit_depth,unsigned char *src,int w_Src,int h_Src)
{
	int sw = w_Src-1, sh = h_Src-1, dw = w_Dest-1, dh = h_Dest-1;
	int B, N, x, y;
	int nPixelSize = bit_depth/8;
	unsigned char *pLinePrev,*pLineNext;
	unsigned char *pDest = new unsigned char[w_Dest*h_Dest*bit_depth/8];
	unsigned char *tmp;
	unsigned char *pA,*pB,*pC,*pD;

	for(int i=0;i<=dh;++i)
	{
		tmp =pDest + i*w_Dest*nPixelSize;
		y = i*sh/dh;
		N = dh - i*sh%dh;
		pLinePrev = src + (y++)*w_Src*nPixelSize;

		pLineNext = (N==dh) ? pLinePrev : src+y*w_Src*nPixelSize;

		for(int j=0;j<=dw;++j)
		{
			x = j*sw/dw*nPixelSize;
			B = dw-j*sw%dw;
			pA = pLinePrev+x;
			pB = pA+nPixelSize;
			pC = pLineNext + x;
			pD = pC + nPixelSize;
			if(B == dw)
			{
				pB=pA;
				pD=pC;
			}

			for(int k=0;k<nPixelSize;++k)
			{
				*tmp++ = ( unsigned char )( int )(
					( B * N * ( *pA++ - *pB - *pC + *pD ) + dw * N * *pB++
					+ dh * B * *pC++ + ( dw * dh - dh * B - dw * N ) * *pD++
					+ dw * dh / 2 ) / ( dw * dh ) );
			}
		}
	}
	return pDest;
}
