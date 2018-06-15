#include <iostream>
#include "cv.h"
#include "highgui.h"

using std::cout;
using std::endl;

// 加载一副图像，设置自己的ROI(感兴趣区域)，做些修改
// 将ROI区域中的像素都加上一个整数

int main()
{
	IplImage* src;
	src = cvLoadImage("D:\\JPG\\0.jpg");
	// 设置自己的感兴趣的区域
	cvSetImageROI(src, cvRect(0, 0, 100, 100));
	cvAddS(src, cvScalar(50), src);
	// 取消ROI区域的设置
	cvResetImageROI(src);
	cvNamedWindow("Roi_Add");
	cvShowImage("Roi_Add", src);
	cvWaitKey();

	system("pause");
	return 0;
}