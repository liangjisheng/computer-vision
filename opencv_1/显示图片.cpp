#include "highgui.h"

int main()
{
	IplImage* src=cvLoadImage("F:\\OpenCV\\Data\\1.jpg");
	cvNamedWindow("ShowImage",CV_WINDOW_AUTOSIZE);
	cvShowImage("ShowImage",src);
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvDestroyWindow("ShowImage");
	return 0;

}