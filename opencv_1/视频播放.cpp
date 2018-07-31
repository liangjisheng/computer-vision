#include "highgui.h"

int main()
{
	CvCapture* capture=cvCreateFileCapture("F:\\OpenCV\\Data\\Sample.avi");
	IplImage* frames;
    cvNamedWindow("AviShow");
	while(1)
	{
		frames=cvQueryFrame(capture);
		if(!frames)
		{
			break;
		}
		cvShowImage("AviShow",frames);
		if(cvWaitKey(33)==27)
		{
			break;
		}
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("AviShow");
	return 0;
}