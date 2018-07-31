#include "cv.h"
#include "highgui.h"

int main()
{
	cvNamedWindow("ImageIn");
	cvNamedWindow("ImageOut");
	IplImage*  scr_in=cvLoadImage("F:\\OpenCV\\Data\\1.jpg");
	IplImage*  scr_out=cvCreateImage(cvGetSize(scr_in),IPL_DEPTH_8U,3);
	cvSmooth(scr_in,scr_out,CV_GAUSSIAN,3,3);
	cvShowImage("ImageIn",scr_in);
	cvShowImage("ImageOut",scr_out);
	cvWaitKey(0);
	cvReleaseImage(&scr_in);
	cvReleaseImage(&scr_out);
	return 0;
}