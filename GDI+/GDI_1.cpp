
// ¶ÁÈ¡jpgÍ¼ÏñÏñËØrgbÖµ

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <GdiPlus.h>

using namespace std;
using namespace Gdiplus;

int main()
{
	GdiplusStartupInput gidplusstartupinput;
	ULONG_PTR gdiplustoken;

	GdiplusStartup(&gdiplustoken, &gidplusstartupinput, NULL);

	wstring infilename(L"test.jpg");
	string outfilename("color.txt");

	Bitmap *bmp = new Bitmap(infilename.c_str());
	UINT height = bmp->GetHeight();
	UINT width = bmp->GetWidth();
	cout << "width: " << width << ", height: " << height << endl;

	Color color;
	ofstream fout(outfilename.c_str());

	for (UINT y = 0; y < height; ++y)
		for (UINT x = 0; x < width; ++x)
		{
			bmp->GetPixel(x, y, &color);
			fout << x << ";" << y << ";"
				<< (int)color.GetRed() << ";"
				<< (int)color.GetGreen() << ";"
				<< (int)color.GetBlue() << endl;
		}

	fout.close();
	delete bmp;

	GdiplusShutdown(gdiplustoken);

	system("pause");
	return 0;
}