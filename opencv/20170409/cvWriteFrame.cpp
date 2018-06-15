// 一个完整的程序来实现一个彩色视频文件并以灰度格式输出这个视频文件
#include "cv.h"
#include "highgui.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	CvCapture* capture = NULL;
	capture = cvCreateFileCapture("julia.avi");
	if(!capture)
		return -1;

	IplImage* bgr_frame = cvQueryFrame(capture);
	// frame pre second 帧率
	double fps = cvGetCaptureProperty(capture,
		CV_CAP_PROP_FPS);
	CvSize size = cvSize(
		(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
		(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT)
		);

	CvVideoWriter* writer = cvCreateVideoWriter(
		"julia_copy.avi",
		CV_FOURCC('M', 'J', 'P', 'G'),
		fps,
		size);

	IplImage* logploar_frame = cvCreateImage(
		size,
		IPL_DEPTH_8U,
		3);

	while((bgr_frame = cvQueryFrame(capture)) != NULL)
	{
		// 转换为对数极坐标格式
		cvLogPolar(bgr_frame, 
			logploar_frame,
			cvPoint2D32f(bgr_frame->width / 2, bgr_frame->height / 2),
			40,
			CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
		cvWriteFrame(writer, logploar_frame);
	}

	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&logploar_frame);
	cvReleaseCapture(&capture);

	system("pause");
	return 0;
}