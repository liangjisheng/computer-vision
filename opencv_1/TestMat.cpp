
/*
 name: TestMat.cpp
 func: Mat图像类的测试
*/

#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/opencv.hpp>
//opencv2\core\core.hpp
//#include <opencv/cv.h>
// #include <opencv/cv.hpp>

void test();
void test1();

using namespace cv;

int main()
{
	//test();
	test1();

	system("pause");
	return 0;
}

void test()
{
	const char *lpszImg = "lena.jpg";
	Mat img = imread(lpszImg);
	if (img.empty())
	{
		cout << "Can not load image " << lpszImg << endl;
		return ;
	}

	const char *lpszWin = "img";
	imshow(lpszWin, img);
	waitKey();

	// 不销毁会有问题
	destroyWindow(lpszWin);
}

void test1()
{
	// BGR
	Mat img(640, 480, CV_8UC3, Scalar(0, 0, 255));
	if (img.empty())
	{
		cout << "Can not load image" << endl;
		return;
	}

	const char *lpszWin = "img";
	namedWindow(lpszWin, CV_WINDOW_AUTOSIZE);
	imshow(lpszWin, img);
	waitKey();

	destroyWindow(lpszWin);
}
