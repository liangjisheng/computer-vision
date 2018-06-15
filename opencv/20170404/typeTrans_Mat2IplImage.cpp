// 出于兼容性的考虑，opencv依然是支持C语言接口的IplImage和CvMat结构。

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	// Mat to IplImage
	Mat img(Size(320, 240), CV_8UC3);

	for(int i = 0; i < img.rows; ++i)
	{
		for(int j = 0; j < img.cols; ++j)
		{
			Vec3b pixel;
			pixel[0] = rand() % 255;
			pixel[1] = rand() % 255;
			pixel[2] = rand() % 255;
			img.at<Vec3b>(i, j) = pixel;
		}
	}

	imshow("img", img);
	waitKey(0);

	IplImage iplimg = img;	// to IplImage
	CvMat cvimg = img;		// to CvMat
	// 特别要注意，类型转换后，IplImage和CvMat与Mat共用同一矩阵数据，
	// 而IplImage和CvMat没有引用计数功能，如果img中数据被释放iplimg和
	// cvimg也就失去了数据


	Mat im(&iplimg, true);		// true表示Mat会新申请内存，然后将
	// 数据复制到Mat的数据区，false表示共用数据，默认为false,
	// 建议为true,内存管理会简单

	system("pause");
	return 0;
}