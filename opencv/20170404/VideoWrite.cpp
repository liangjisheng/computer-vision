
// 创建视屏是需要制定一系列参数，包括文件名，编解码器，帧率，宽度和
// 高度。编解码器使用4个字符表示，可以是CV_FOURCC('M','J','P','G')
// CV_FOURCC('X','V','I','D'), CV_FOURCC('D','I','V','X')
// 如果使用某种编解码器无法创建视屏文件，请尝试其它编解码器

// 本例写一个视屏文件，第0帧上是一个红色的0，第1帧上是一个红色的1
// 以此类推

#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	// 定义视屏的宽度和高度
	Size s(640,480);
	// 创建writer,并指定FOURCC及FPS参数
	VideoWriter writer = VideoWriter("myvideo.avi", 
		CV_FOURCC('M', 'J', 'P', 'G'), 25, s);
	// 检查是否创建成功
	if(!writer.isOpened())
	{
		cerr << "Can not create video file.\n" << endl;
		return -1;
	}

	Mat frame(s, CV_8UC3);

	for(int i = 0; i < 100; ++i)
	{
		// 将图像设置成黑色
		frame = Scalar::all(0);
		// 将整数i转为i字符串类型
		char text[128] = {0};
		sprintf(text, "%d", i);
		// 将数字回到画面上
		putText(frame, text, Point(s.width / 3, s.height / 2),
			FONT_HERSHEY_SCRIPT_SIMPLEX, 3, Scalar(0, 0, 255), 3, 8);

		// 将图像写入视屏
		writer << frame;
	}

	// 退出程序时会自动关闭视屏文件
	system("pause");
	return 0;
}