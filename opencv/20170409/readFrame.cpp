#include <iostream>
#include "highgui.h"

int main()
{
	cvNamedWindow("test2", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("julia.avi");
	IplImage* frame;

	while(1)
	{
		frame = cvQueryFrame(capture);
		if(!frame)
			break;
		cvShowImage("test2", frame);

		// 程序暂停33毫秒，获取下一帧图片
		// c被设置成按键的ASCII码，否则c被设置成-1.
		char c = cvWaitKey(1);
		if(c == 27)			// ESC(ASCII 27)
			break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("test2");

	system("pause");
	return 0;
}