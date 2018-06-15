
// 用fopen打开一个bmp文件，请问怎样取得它的HDIB句柄？
// MSDN中对HDIB的运用是：ＢＭＰ文件除去文件头（ＢＩＴＭＡＰＦＩＬＥＨＥＡＤＥＲ）
// 以后的所有内容。当然你也可以定义其批向ＢＭＰ文件的点阵信息！
// HDIB是要你自己获得的，它不过是个内存句柄而已，用GlobalAlloc分配一块用于保存位图数据 
// 的内存，返回值就是一个HDIB，不过，内存里面一定要有图像数据

BOOL ReadDIBFile(LPCTSTR   strFileName)
{   
  BITMAPFILEHEADER   bmfHeader;   
  DWORD   dwBitsSize;   
  HDIB   hDIB;   
  LPSTR   pDIB;   
    
  CFile   file;   
  if(!file.Open(strFileName,CFile::modeRead))   
  {   
	TRACE("failed   to   open   img   file\n");   
	return   FALSE;   
  }   
  //   获取DIB（文件）长度（字节）   
  dwBitsSize   =   file.GetLength();   
    
  //   尝试读取DIB文件头   
  if   (file.Read((LPSTR)&bmfHeader,   sizeof(bmfHeader))   !=   sizeof(bmfHeader))   
  {   
	TRACE("failed   to   read   image   file\n");   
	file.Close();   
	return   FALSE;   
  }   
    
  //   判断是否是DIB对象，检查头两个字节是否是"BM"   
  if   (bmfHeader.bfType   !=   DIB_HEADER_MARKER)   
  {   
	TRACE("not   a   valid   bmp   file\n");   
	file.Close();   
	return   FALSE;   
  }   
    
  //   为DIB分配内存   
  hDIB   =   (HDIB)   ::GlobalAlloc(GMEM_MOVEABLE   |   GMEM_ZEROINIT,   dwBitsSize);   
  if   (hDIB   ==   0)   
  {   
    TRACE("failed   to   alloc   memory   when   read   img   file   to   buffer\n");   
	return   FALSE;   
  }   
    
  //   锁定   
  pDIB   =   (LPSTR)   ::GlobalLock((HGLOBAL)   hDIB);   
    
  //   读象素   
  if (file.ReadHuge(pDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) !=
			dwBitsSize - sizeof(BITMAPFILEHEADER))
  {   
	TRACE("not   a   valid   file   length\n");
	::GlobalUnlock((HGLOBAL)   hDIB);   
	::GlobalFree((HGLOBAL)   hDIB);   
	return   FALSE;   
  }   
    
  file.Close();   
  return   TRUE;   
}