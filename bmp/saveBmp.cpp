
#include <iostream>
#include <stdio.h>
#include <Windows.h>

using std::cout;
using std::endl;

// 将一个正弦曲线写入24位的BMP
void saveBitmap()
{
	// define bmp size
	const int height = 600;
	const int width = 800;
	const int size = height * width * 3;
	double x, y;
	int index;

	BITMAPFILEHEADER fileHeader;
	fileHeader.bfType = 0x4d42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size;

	BITMAPINFOHEADER infoHeader = {0};
	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biHeight = height;
	infoHeader.biWidth = width;
	infoHeader.biPlanes = 3;
	infoHeader.biBitCount = 24;
	infoHeader.biSizeImage = 24;
	infoHeader.biCompression = 0;	// BI_RGB

	unsigned char *bits = new unsigned char[size];
	memset(bits, 0xff, size);

	// Sin Graph
	for (x = 0; x < 800; x += 0.5)
	{
		y = sin(x / 100.0) * 200 + 300;
		index = (int)y * 800 * 3 + (int)x * 3;

		bits[index + 0] = 255;	// Blue
		bits[index + 1] = 0;	// Green
		bits[index + 2] = 0;	// Red
	}

	FILE *f = fopen("output.bmp", "wb");
	if (NULL == f)
	{
		cout << "open file failed" << endl;
		return ;
	}

	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f);
	fwrite(bits, size, 1, f);
	fclose(f);

	free(bits);
}


int main()
{
	saveBitmap();

	system("pause");
	return 0;
}
