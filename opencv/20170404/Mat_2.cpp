
// Mat 增加了迭代器的支持，用于矩阵元素的遍历

#include <iostream>
#include <ctime>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	Mat grayim(600, 800, CV_8UC1);
	Mat colorim(600, 800, CV_8UC3);

	srand(time(0));
	// 遍历所有像素，设置像素值
	MatIterator_<uchar> grayit, grayend;
	for(grayit = grayim.begin<uchar>(), grayend = grayim.begin<uchar>();
		grayit != grayend; ++grayit)
		*grayit = rand() % 255;

	MatIterator_<Vec3b> colorit, colorend;
	for(colorit = colorim.begin<Vec3b>(), colorend = colorim.begin<Vec3b>();
		colorit != colorend; ++colorit)
	{
		(*colorit)[0] = rand() % 255;	// B
		(*colorit)[1] = rand() % 255;	// G
		(*colorit)[2] = rand() % 255;	// R
	}

	imshow("grayim",grayim);
	imshow("colorim", colorim);
	waitKey(0);

	system("pause");
	return 0;
}