#include <iostream>
#include "cv.h"
#include "highgui.h"

using std::cout;
using std::endl;

// 使用cvPyrDown()创建一副宽度和高度为输入图像一半尺寸的图像
IplImage* doPyrDown(IplImage* In, int filter = IPL_GAUSSIAN_5x5)
{
	// Best to make sure input image is divisible by two
	assert(0 == In->width % 2 && 0 == In->height % 2);

	// 分配新的图像空间(即内存)
	IplImage* Out = cvCreateImage(
		cvSize(In->width / 2, In->height / 2),
		In->depth,
		In->nChannels);
	cvPyrDown(In, Out);
	return Out;
}

int main()
{
	IplImage* In;
	In = cvLoadImage("D:\\JPG\\0.jpg");
	cout << "In->width = " << In->width << endl;
	cout << "In->height = " << In->height << endl;
	cout << "In->depth = " << In->depth << endl;
	cout << "In->nChannels = " << In->nChannels << endl;
	cout << "In->align = " << In->align << endl;
	cout << "In->alphaChannel = " << In->alphaChannel << endl;
	cout << "In->BorderConst = " << In->BorderConst << endl;
	cout << "In->BorderMode = " << In->BorderMode << endl;
	cout << "In->channelSeq = " << In->channelSeq << endl;
	cout << "In->colorModel = " << In->colorModel << endl;
	cout << "In->dataOrder = " << In->dataOrder << endl;
	cout << "In->ID = " << In->ID << endl;
	//cout << "In->imageData = " << In->imageData << endl;
	//cout << "In->imageDataOrigin = " << In->imageDataOrigin << endl;
	//cout << In->imageId << endl;
	cout << "In->imageSize = " << In->imageSize << endl;
	//cout << In->maskROI << endl;
	cout << "In->nSize = " << In->nSize << endl;
	cout << "In->origin = " << In->origin << endl;
	//cout << In->roi << endl;
	cout << "In->tileInfo = " << In->tileInfo << endl;
	cout << "In->widthStep = " << In->widthStep << endl;

	cvNamedWindow("In");
	cvNamedWindow("Out");

	// 在函数中，分配新的内存，返回指针
	IplImage* Out = doPyrDown(In);

	cvShowImage("In", In);
	cvShowImage("Out", Out);
	cvWaitKey(0);

	system("pause");
	return 0;
}