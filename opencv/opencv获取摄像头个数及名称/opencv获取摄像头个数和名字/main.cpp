#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
int main()
{
	cv::VideoCapture cap;
	int devicenumber = 0;
	std::vector<std::string> devicename;
	int deviceCount = cap.getDeviceCount();
	std::cout<<deviceCount<<std::endl;
	for (int i=0;i<deviceCount;i++)
	{
		string deviceName = cap.getDeviceName(i);
		std::cout<<deviceName<<std::endl;
	}

}