
/*
 name: GetPixel.cpp
 func: 遍历图像
*/

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void test();
void test1();

int main()
{
	// test();
	test1();

	system("pause");
	return 0;
}

void test()
{
	Mat grayim(600, 800, CV_8UC1);
	Mat colorim(600, 800, CV_8UC3);

	// 遍历所有像素
	// 如果要遍历图像，并不推荐使用 at()函数。使用这个函数的
	// 优点是代码的可读性高，但是效率并不是很高
	for (int i = 0; i < grayim.rows; ++i)
		for (int j = 0; j < grayim.cols; ++j)
			grayim.at<uchar>(i, j) = (i + j) % 255;

	for (int i = 0; i < colorim.rows; ++i)
		for (int j = 0; j < colorim.cols; ++j)
		{
			Vec3b pixel;
			pixel[0] = i % 255;
			pixel[1] = j % 255;
			pixel[2] = 0;
			colorim.at<Vec3b>(i, j) = pixel;
		}

	imshow("grayim", grayim);
	imshow("colorim", colorim);
	waitKey();

	destroyWindow("grayim");
	destroyWindow("colorim");
}

void test1()
{
	Mat grayim(600, 800, CV_8UC1);
	Mat colorim(600, 800, CV_8UC3);

	// 遍历所有像素，设置像素值
	MatIterator_<uchar> grayit, grayend;
	for (grayit = grayim.begin<uchar>(), grayend = grayim.end<uchar>();
		grayit != grayend; ++grayit)
	{
		*grayit = rand() % 255;
	}

	MatIterator_<Vec3b> colorit, colorend;
	for (colorit = colorim.begin<Vec3b>(), colorend = colorim.end<Vec3b>();
		colorit != colorend; ++colorit)
	{
		(*colorit)[0] = rand() % 255;	// B
		(*colorit)[1] = rand() % 255;	// G
		(*colorit)[2] = rand() % 255;	// R
	}

	imshow("grayim", grayim);
	imshow("colorim", colorim);
	waitKey();

	destroyWindow("grayim");
	destroyWindow("colorim");
}
