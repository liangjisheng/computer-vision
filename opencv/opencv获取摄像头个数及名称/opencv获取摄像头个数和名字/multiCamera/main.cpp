
#include "highgui.hpp"
#include <iostream>

int main()
{
	cv::VideoCapture cap;
	int deviceCount = cap.getDeviceCount();
	std::cout<<"����ͷ��������"<<deviceCount<<std::endl;
	for (int i=0;i<deviceCount;i++)
	{
		std::string deviceName = cap.getDeviceName(i);
		std::cout<<"����ͷ "<<i<<" �����֣�"<<deviceName<<std::endl;
	}
	std::cout<<std::endl;
}