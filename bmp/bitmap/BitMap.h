
// 调色板：现在的计算机大都是32位或是更高，于是图像数据可用真彩色24位表达的，
// 即每个像素均由24bit表示，每8bit表示RGB三色中的一色。但以前的计算机处理能力
// 较差，图像用1位、4位或8位，即BITMAPINFOHEADER中的biBitCount不是24，这时又
// 想表达出RGB色彩就需要调色板，调色板即使将图像数据中使用的一种颜色对应到RGB
// 颜色中，这样图像数据中的像素值就是一个索引值，真正的像素值是这个索引值对应
// 的调色板中的值。调色板是一个数组，数组中每个元素就是一个rgb颜色，对于8位图像
// 最多可表达256种颜色，调色板的大小就是256
// 调色板数组中每个元素的数据结构如下：

//typedef struct tagRGBQUAD
//{
//	BYTE rgbBlue;
//	BYTE rgbGreen;
//	BYTE rgbRed;
//	BYTE rgbReserved;
//}RGBQUAD;
//
//typedef RGBQUAD FAR* LPRGBQUAD;

// 图像数据对于1位图像，1个像素用1bit存储，对于24位图像，1个像素用24bit存储。
// 位图文件的数据是从下而上，从左而右存储的。所以说，读取的时候，最先读到的是
// 图像左下方的像素，最后读取的是图像右上方的图像

/**
 * 类说明：C++实现位图文件的读取与存储
*/

#ifndef _MY_BITMAP_H_
#define _MY_BITMAP_H_

#include <Windows.h>

class CBitMap
{
public:
	CBitMap();
	~CBitMap();
protected:
	BITMAPFILEHEADER fileHeader;		// 位图文件头
	BITMAPINFOHEADER infoHeader;		// 位图信息头
public:
	int m_width_p;						// 位图宽度(像素计算)
	int m_height_p;						// 位图高度
	int m_nBitCount;					// 位深
	unsigned char *databuf;				// 实际图像数据
	LPRGBQUAD colorTable;				// 颜色表(调色板)
	bool Read(char *fileName);			// 读取位图文件
	bool Write(char *fileName);			// 将数据写入位图文件中
};

#endif // _MY_BITMAP_H_