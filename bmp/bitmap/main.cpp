
#include "BitMap.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	CBitMap *bmp = new CBitMap();
	// bmp->Read("liangjisheng.bmp");
	if (bmp->Read("1.bmp"))
	{
		cout << "Read bmp file ok" << endl;
		if (bmp->Write("2.bmp"))
			cout << "write to 2.bmp ok" << endl;
		else
			cout << "write to 2.bmp failed" << endl;
	}
	else
		cout << "Read bmp file failed" << endl;

	system("pause");
	return 0;
}