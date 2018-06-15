
#include <iostream>
#include "opencv2/core/core.hpp";

using std::cout;
using std::endl;
using namespace cv;

// opencv中预定义了一些小向量
typedef Vec<uchar, 2> Vec2b;
typedef Vec<uchar, 3> Vec3b;
typedef Vec<uchar, 4> Vec4b;

typedef Vec<short, 2> Vec2s;
typedef Vec<short, 2> Vec3s;
typedef Vec<short, 2> Vec4s;

typedef Vec<int, 2> Vec2i;
typedef Vec<int, 3> Vec3i;
typedef Vec<int, 4> Vec4i;

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;
typedef Vec<float, 4> Vec6f;

typedef Vec<double, 2> Vec2d;
typedef Vec<double, 3> Vec3d;
typedef Vec<double, 4> Vec4d;
typedef Vec<double, 4> Vec6d;

int main()
{
	Mat z = Mat::zeros(2, 3, CV_8UC1);
	cout << "z = " << endl << " " << z << endl;

	// 未声明通道数，默认表示单通道
	Mat O = Mat::ones(2, 3, CV_32F);
	cout << "O = " << endl << " " << O << endl;

	Mat E = Mat::eye(2, 3, CV_64F);
	cout << "E = " << endl << " " << E << endl;

	system("pause");
	return 0;
}