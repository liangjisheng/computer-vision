
#include "highgui.hpp"
#include <iostream>

int main()
{
	cv::VideoCapture cap;
	int deviceCount = cap.getDeviceCount();
	std::cout<<"摄像头的数量："<<deviceCount<<std::endl;
	for (int i=0;i<deviceCount;i++)
	{
		std::string deviceName = cap.getDeviceName(i);
		std::cout<<"摄像头 "<<i<<" 的名字："<<deviceName<<std::endl;
	}
	std::cout<<std::endl;
}