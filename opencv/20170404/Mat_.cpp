
// Mat_类是对Mat类的一个包装，定义如下：
// template<typename _Tp> class Mat_ : public Mat
//{
//public:
	// 只定义了几个方法
	// 没有定义新的属性
//};

#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	Mat M(600, 800, CV_8UC1);

	for(int i = 0; i < M.rows; ++i)
	{
		// 获取指针时需要指定类型
		uchar* p = M.ptr<uchar>(i);
		for(int j = 0; j < M.cols; ++j)
		{
			double d1 = (double) ((i + j) % 255);
			// 用at()读写像素是，需要指定类型
			M.at<uchar>(i, j) = d1;
			double d2 = M.at<uchar>(i,j);
		}
	}

	// Mat_类在变量声明是指定矩阵元素类型
	Mat_<uchar> M1 = (Mat_<uchar>&)M;

	for(int i = 0; i < M1.rows; ++i)
	{
		// 不需制定元素类型，语法简洁
		uchar* p = M1.ptr(i);
		for(int j = 0; j < M1.cols; ++j)
		{
			double d1 = (double) ((i + j) % 255);
			// 直接使用matlab风格的矩阵元素读写,简洁
			M1(i, j) = d1;
			double d2 = M1(i, j);
		}
	}

	system("pause");
	return 0;
}