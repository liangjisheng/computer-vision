#include "cv.h"
#include "highgui.h"

CvCapture * g_capture=NULL;
int         g_slider_pos=0;
int         fram_count=0;

void OnTrackbarSlider(int pos)
{
	cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
	fram_count=pos;
}


int main()
{
	cvNamedWindow("show");
    g_capture=cvCreateFileCapture("F:\\OpenCV\\Data\\Sample.avi");
	int frams=(int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
	if(frams>0)
	{
		cvCreateTrackbar("Position","show",&g_slider_pos,frams,OnTrackbarSlider);
	}
	IplImage *frame;

	while(1)
	{
		frame=cvQueryFrame(g_capture);
		if(!frame)
		{
			break;
		}
		cvShowImage("show",frame);
		char c=cvWaitKey(100);
		if(c==27)
		{
			break;
		}
		cvSetTrackbarPos("Position","show",fram_count);
		fram_count++;

	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("show");
	return 0;
}