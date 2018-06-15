
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

int main()
{
	FILE *fp = fopen("1.bmp", "rb");
	if (NULL == fp)
	{
		cout << "open image failed" << endl;
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	int nlen = ftell(fp);
	// 使得读文件指针回到文件头位置
	rewind(fp);

	unsigned char *imagebuf = new unsigned char[nlen];
	fread(imagebuf, nlen, 1, fp);
	fclose(fp);
	fp = NULL;

	fp = fopen("2.bmp", "wb");
	if (NULL == fp)
	{
		cout << "open file failed" << endl;
		return -2;
	}
	fwrite(imagebuf, nlen, 1, fp);
	cout << "done" << endl;

	fclose(fp);
	free(imagebuf);
	imagebuf = NULL;

	system("pause");
	return 0;
}
