
// 可以使用指针访问数据
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	Mat grayim(600, 800, CV_8UC1);
	Mat colorim(600, 800, CV_8UC3);

	// 遍历所有像素，设置像素值
	for(int i = 0; i < grayim.rows; ++i)
	{
		// 获取第i行首像素指针
		uchar* p = grayim.ptr<uchar>(i);
		// 对第i行的每个像素(byte)操作
		for(int j = 0; j < grayim.cols; ++j)
			p[j] = (i + j) % 255;
	}

	for(int i = 0; i < colorim.rows; ++i)
	{
		Vec3b* p = colorim.ptr<Vec3b>(i);
		for(int j = 0; j < colorim.cols; ++j)
		{
			p[j][0] = i % 255;	// B
			p[j][1] = j % 255;	// G
			p[j][2] = 0;		// R
		}
	}

	imshow("grayim", grayim);
	imshow("colorim", colorim);
	waitKey(0);

	system("pause");
	return 0;
}