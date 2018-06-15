#include <iostream>
#include "cv.h"
#include "highgui.h"

// 此程序加上滚动条，实现快速拖动视频文件
// 添加一个全局变量表示滚动条的位置，
// 以及一个回调函数更新变量，重新设置视频读入位置

int g_slider_position = 0;
// 回调函数需要CvCapture对象，因此定义为全局
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(g_capture,
		CV_CAP_PROP_POS_FRAMES,			// 表示以帧数来设置读入位置
		pos);
}


int main()
{
	cvNamedWindow("test3", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture("julia.avi");
	// 获取视频文件的总帧数
	int frames = (int)cvGetCaptureProperty(
		g_capture,
		CV_CAP_PROP_FRAME_COUNT);
	std::cout << frames << std::endl;

	if(frames !=0)
	{
		cvCreateTrackbar(
			"Position",			// 滚动条名称
			"test3",			// 滚动条所属窗口
			&g_slider_position,
			frames,
			onTrackbarSlide);
	}

	IplImage* frame;

	while(1)
	{
		frame = cvQueryFrame(g_capture);
		if(!frame)
			break;
		cvShowImage("test2", frame);

		// 程序暂停33毫秒，获取下一帧图片
		// c被设置成按键的ASCII码，否则c被设置成-1.
		char c = cvWaitKey(33);
		if(c == 27)			// ESC(ASCII 27)
			break;
	}

	cvReleaseCapture(&g_capture);
	cvDestroyWindow("test2");

	system("pause");
	return 0;
}
