
// VideoCapture既可以从视屏文件读取图像，也可以从摄像头读取图像
// 可以使用该类的构造函数打开视屏文件或者摄像头

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	// 打开视屏文件
	VideoCapture cap("test.avi");

	// 检查是否成功打开
	if(!cap.isOpened())
	{
		cerr << "Can not open a camera or file." << endl;
		return -1;
	}

	Mat edges;
	namedWindow("edges", 1);

	for(;;)
	{
		Mat frame;
		cap >> frame;	// 读一帧，存到frame
		if(frame.empty())
			break;
		// 将读到的图像转换为灰度图
		cvtColor(frame, edges, CV_BGR2GRAY);
		// 进行边缘提取操作
		Canny(edges, edges, 0, 30, 3);
		
		imshow("edges", edges);

		// 等待30ms，如果又键按下，则退出循环
		if(waitKey(30) >= 0)
			break;
	}

	// 退出时会自动释放cap中占用的资源
	system("pause");
	return 0;
}