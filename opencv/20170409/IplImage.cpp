#include <iostream>
#include "highgui.h"

int main()
{
	// 通过文件名确定被加载文件的格式，自动分配图像数据结构所需的内存
	IplImage* img = cvLoadImage("D:\\JPG\\0.jpg");

	// 创建窗口，第一个参数为窗口标题
	cvNamedWindow("test1", CV_WINDOW_AUTOSIZE);

	cvShowImage("test1", img);

	// 使程序暂停，等待用户触发一个按键操作，如果大于0，则程序暂停执行
	// 相应的毫秒数，然后继续执行，即使没有按键按下. 0则等待用户触发按键操作
	cvWaitKey(0);

	cvReleaseImage(&img);

	cvDestroyWindow("test1");

	system("pause");
	return 0;
}