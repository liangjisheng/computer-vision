
#include "BitMap.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

CBitMap::CBitMap() 
{
	memset(&fileHeader, 0, sizeof(BITMAPFILEHEADER));
	memset(&infoHeader, 0, sizeof(BITMAPINFOHEADER));
	m_width_p = 0;
	m_width_p = 0;
	m_nBitCount = 0;
	databuf = NULL;
	colorTable = NULL;
}

CBitMap::~CBitMap()
{
	if (databuf)
	{
		delete [] databuf;
		databuf = NULL;
	}
	if (colorTable)
	{
		delete [] colorTable;
		colorTable = NULL;
	}
}

// read bitmap info from a file
bool CBitMap::Read(char *fileName)
{
	FILE *f = fopen(fileName, "rb");
	if (NULL == f)
		return false;

	// 读取位图文件头
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f);
	// 读取位图信息头
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f);

	m_width_p = infoHeader.biWidth;
	m_height_p = infoHeader.biHeight;
	m_nBitCount = infoHeader.biBitCount;

	// if colorTable exist, read colorTable
	if (1 == m_nBitCount)
	{
		colorTable = new RGBQUAD[2];
		fread(colorTable, sizeof(RGBQUAD), 2, f);
	}
	else if (4 == m_nBitCount)
	{
		colorTable = new RGBQUAD[16];
		fread(colorTable, sizeof(RGBQUAD), 16, f);
	}
	else if (8 == m_nBitCount)
	{
		colorTable = new RGBQUAD[256];
		fread(colorTable, sizeof(RGBQUAD), 256, f);
	}

	// read image data
	databuf = new unsigned char[infoHeader.biSizeImage];
	memset(databuf, 0, infoHeader.biSizeImage);
	size_t nRet = fread(databuf, 1, infoHeader.biSizeImage, f);

	fclose(f);
	return true;
}

// write bitmap info to a file
bool CBitMap::Write(char *fileName)
{
	FILE *f = fopen(fileName, "wb");
	if (NULL == f)
		return false;

	// if m_nBitCount is 24 there is no color table
	// if m_nBitCount is 8, the size of color table is 256 * 4, 4B is the size of RGBQUAD
	int colorTableSize = 0;
	if (m_nBitCount == 8)
		colorTableSize = sizeof(RGBQUAD) * 256;

	// the size of the herder of bmp file
	int headerSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize;
	// the size of each line in bmp file
	int lineSize = (m_width_p * m_nBitCount / 8 + 3) / 4 * 4;
	// the size of the image data of bmp file
	int dataSize = lineSize * m_height_p;

	// set the attribute of BITMAPFILEHEADER
	fileHeader.bfType = 0x4d42;
	fileHeader.bfSize = headerSize + dataSize;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = headerSize;

	// set the attribute of BITMAPINFOHEADER
	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biWidth = m_width_p;
	infoHeader.biHeight = m_height_p;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = m_nBitCount;
	infoHeader.biCompression = BI_RGB;
	infoHeader.biSizeImage = dataSize;
	infoHeader.biClrImportant = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;

	//write the data of BITFILEHEADER to bmp file
	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f);
	//write the data of BITINFOHEADER to bmp file
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f);

	if (8 == m_nBitCount)
	{
		//if (colorTable)
		//{
		//	delete [] colorTable;
		//	colorTable = NULL;
		//}
		// colorTable = new RGBQUAD[256];
		fwrite(&colorTable, sizeof(RGBQUAD), 256, f);
	}

	// write the image data to bmp file
	int len = strlen((char *)databuf);
	size_t nRet = fwrite(databuf, 1, dataSize, f);

	fclose(f);
	return true;
}