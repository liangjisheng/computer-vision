
// Mat类，默认情况下输出的格式是类似matlab中矩阵的输出格式
// 除了默认格式，Mat也支持其他的输出格式。

#include <iostream>
#include "opencv2/opencv.hpp";

using namespace std;
using namespace cv;

int main()
{
	Mat R = Mat(3, 2, CV_8UC3);
	
	for(int i = 0; i < R.rows; ++i)
	{
		for(int j = 0; j < R.cols; j++)
		{
			Vec3b pixel;
			pixel[0] = rand() % 255;		// B
			pixel[1] = rand() % 255;		// G
			pixel[2] = rand() % 255;		// R
			R.at<Vec3b>(i, j) = pixel;
		}
	}

	// matlab格式输出
	cout << "R (default) = " << endl << R << endl << endl;

	// python格式输出
	cout << "R (python) = " << endl << format(R, "python") << endl << endl;

	// 已逗号分割的输出
	cout << "R (csv) = " << endl << format(R, "csv") << endl << endl;

	// numpy格式输出
	cout << "R (numpy) = " << endl << format(R, "numpy") << endl << endl;

	// c语言格式输出
	cout << "R (c) = " << endl << format(R, "C") << endl << endl;



	// 二维点
	Point2f P(5, 1);
	cout << "Point (2D) = " << P << endl << endl;

	// 三维点
	Point3f P3f(2, 6, 7);
	cout << "Point (3D) = " << P3f << endl << endl;

	system("pause");
	return 0;
}