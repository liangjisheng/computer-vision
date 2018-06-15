
#include <iostream>

#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main()
{
	IplImage* src;

	src = cvLoadImage("D:\\InstallSoftware\\JPG\\1.jpg", -1);
	if(!src)
		return -1;

	cvSaveImage("D:\\InstallSoftware\\JPG\\1.bmp", src);
	cvReleaseImage(&src);
	cout << "convert successfully" << endl;
	
	system("pause");
	return 0;
}