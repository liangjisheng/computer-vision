#include "cv.h"
#include "highgui.h"

int main()
{
	cvNamedWindow("ImageIn");
	cvNamedWindow("ImageOut");
	IplImage*  scr_in=cvLoadImage("F:\\OpenCV\\Data\\1.jpg");
	assert(scr_in->width%2==0 && scr_in->height%2==0);
	
	IplImage*  scr_out=cvCreateImage(cvSize(scr_in->width/2,scr_in->height/2),scr_in->depth,scr_in->nChannels);
	cvPyrDown(scr_in,scr_out);
	
	cvShowImage("ImageIn",scr_in);
	cvShowImage("ImageOut",scr_out);
	cvWaitKey(0);
	cvReleaseImage(&scr_in);
	cvReleaseImage(&scr_out);
	return 0;
}