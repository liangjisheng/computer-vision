void Rgb2Bmp( const BYTE *pbyRgb, int nWidth, int nHeight, LPCTSTR szFileName )
{
	BITMAPINFOHEADER bih;
	BITMAPFILEHEADER bhh;

	int widthStep = ((((nWidth * 24) + 31) & (~31)) >> 3); //每行实际占用的大小（每行都被填充到一个4字节边界）

	bih.biSize = 40;			// header size
	bih.biWidth = nWidth;
	bih.biHeight = -nHeight;	// 垂直镜像
	bih.biPlanes = 1;
	bih.biBitCount = 24;		// RGB encoded, 24 bit
	bih.biCompression = BI_RGB;	// no compression 非压缩
	bih.biSizeImage = widthStep * nHeight * 3;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0; 

	bhh.bfType = ((WORD)('M' << 8) | 'B');  //'BM'
	bhh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + widthStep * nHeight;
	bhh.bfReserved1 = 0;
	bhh.bfReserved2 = 0;
	bhh.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	int nDIBSize = widthStep * nHeight ;  //buffer的大小 （字节为单位）

	CFile file;
	if( file.Open( szFileName, CFile::modeWrite | CFile::modeCreate ) )
	{
		file.Write( (LPBYTE)&bhh, sizeof(BITMAPFILEHEADER) );
		file.Write( (LPBYTE)&bih, sizeof(BITMAPINFOHEADER) );
		file.Write( pbyRgb, nDIBSize );
		file.Flush();
		file.Close();
	}
}