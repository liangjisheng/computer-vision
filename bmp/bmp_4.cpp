// 在仅获得HBITMAP资源句柄情况下，如何获得这个资源的BITMAP信息

BITMAP bm;  
GetObject(hBitmap,sizeof(BITMAP),&bm);  

//-------------------在内存中建立区域以存放所得位图-------------------  
// hBitmapSrc 为 CBitmap中保存的矩形原图资源句柄  
// hDC 句柄     
// 在内存中开辟位图资源，用以保存原图  
HBITMAP CopyHBitmap(HBITMAP hBitmapSrc,HDC hDC)  
{  
      
    BITMAP bm;  
    HBITMAP hBitmapDst;  
    HDC hdcSrc,hdcDst;  
  
    GetObject(hBitmapSrc,sizeof(BITMAP),&bm);  
    hBitmapDst=CreateCompatibleBitmap(hDC,bm.bmWidth,bm.bmHeight);  
  
    hdcSrc=CreateCompatibleDC(hDC);  
    hdcDst=CreateCompatibleDC(hDC);  
  
    SelectObject(hdcSrc,hBitmapSrc);   
    SelectObject(hdcDst,hBitmapDst);  
  
    BitBlt(hdcDst,0,0,bm.bmWidth,bm.bmHeight,hdcSrc,0,0,SRCCOPY);  
      
    DeleteDC(hdcSrc);  
    DeleteDC(hdcDst);     
    return hBitmapDst;  
  
}  