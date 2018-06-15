#include <iostream>
#include "cv.h"
#include "highgui.h"

using std::cout;
using std::endl;

IplImage* doCanny(
	IplImage* In,
	double lowThres,
	double highThres,
	double aperture = 3
	)
{
	if(In->nChannels != 1)
		return 0;	// Canny only gray scale images
	IplImage* Out = cvCreateImage(
		cvSize(In->width, In->height),
		IPL_DEPTH_8U,
		1);
	cvCanny(In, Out, lowThres, highThres, aperture);
	return Out;
}

int main()
{
	IplImage* In;
	In = cvLoadImage("D:\\JPG\\0.jpg");
	IplImage* Out;
	Out = doCanny(In, 10, 100, 3);

	IplImage* testOut = cvCreateImage(
		cvSize(In->width, In->height),
		IPL_DEPTH_8U,
		1);
	cvCanny(In, testOut, 10, 100, 3);

	cvNamedWindow("In");
	cvNamedWindow("Out");
	//cvNamedWindow("testOut");
	cvShowImage("In", In);
	cvShowImage("Out", Out);
	//cvShowImage("testOut", testOut);
	cvWaitKey(0);

	system("pause");
	return 0;
}