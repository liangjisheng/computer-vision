#include "cv.h"
#include "highgui.h"
#include "stdio.h"

int main()
{
	cvNamedWindow("ImageIn");
	cvNamedWindow("ImageOut");
	IplImage*  scr_in=cvLoadImage("F:\\OpenCV\\Data\\3.jpg",CV_LOAD_IMAGE_UNCHANGED);

    IplImage*  scr_out=cvCreateImage(cvSize(scr_in->width,scr_in->height),scr_in->depth,1);

    cvCanny(scr_in,scr_out,10,100,3);


	
	cvShowImage("ImageIn",scr_in);
	cvShowImage("ImageOut",scr_out);
	cvWaitKey(0);
	cvReleaseImage(&scr_in);
	cvReleaseImage(&scr_out);
	return 0;
}