// 载入一副图像进行平滑处理
#include <cv.h>
#include "highgui.h"
#include <iostream>

using std::cout;
using std::endl;

void smooth(IplImage* pImg)
{
	cvNamedWindow("test_in");
	cvNamedWindow("test_out");
	cvShowImage("test_in", pImg);

	IplImage* pOut = cvCreateImage(
		cvGetSize(pImg),
		IPL_DEPTH_8U,
		3);

	// process
	cvSmooth(pImg, pOut, CV_GAUSSIAN, 3, 3);

	cvShowImage("test_out", pOut);
	cvReleaseImage(&pOut);
	// Wait for the user to hit a key,then clean up the windows
	cvWaitKey(0);
	cvDestroyWindow("test_in");
	cvDestroyWindow("test_out");
}

int main()
{
	IplImage* pImg;
	pImg = cvLoadImage("D:\\JPG\\0.jpg");
	smooth(pImg);
	cvReleaseImage(&pImg);

	system("pause");
	return 0;
}