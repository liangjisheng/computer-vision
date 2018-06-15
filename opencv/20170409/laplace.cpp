
#include <iostream>
#include <cctype>

#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main()
{
	IplImage* laplace = 0;
	IplImage* colorlaplace = 0;
	IplImage* planes[3] = {0, 0, 0};		// 多个图像面
	CvCapture* capture = 0;

	capture = cvCaptureFromCAM(0);
	if(!capture)
	{
		cout << "Could not initialize capturing..." << endl;
		return -1;
	}

	cvNamedWindow("test", 0);

	for(;;)
	{
		IplImage* frame = 0;
		int i;
		frame = cvQueryFrame(capture);
		if(!frame)
			break;

		if(!laplace)
		{
			for(i = 0; i < 3; i++)
				planes[i] = cvCreateImage(cvSize(frame->width, frame->height), 8, 1);
			laplace = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_16S, 1);
			colorlaplace = cvCreateImage(cvSize(frame->width, frame->height), 8, 3);
		}

		cvCvtPixToPlane(frame, planes[0], planes[1], planes[2], 0);
		for(i = 0; i < 3; i++)
		{
			cvLaplace(planes[i], laplace, 3);
			cvConvertScaleAbs(laplace, planes[i], 1, 0);
		}

		cvCvtPlaneToPix(planes[0], planes[1], planes[2], 0, colorlaplace);
		colorlaplace->origin = frame->origin;

		cvShowImage("test", colorlaplace);

		if(cvWaitKey(10) > 10)
			break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("test");

	system("pause");
	return 0;
}