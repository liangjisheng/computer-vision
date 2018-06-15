
#include <iostream>
#include <iomanip>

#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;


void printMat(CvMat* arr)
{
	int i, j;
	for(i = 0;i < arr->rows; i++)
	{
		cout << endl;
		switch(CV_MAT_DEPTH(arr->type))
		{
		case CV_32F:
		case CV_64F:
			for(j = 0; j < arr->cols; j++)
				cout << setprecision(3) << setw(9) << (float)cvGetReal2D(arr, i, j);
			break;

		case CV_8U:
		case CV_16U:
			for(j = 0; j < arr->cols; j++)
				cout << setw(6) << (int)cvGetReal2D(arr, i, j);
			break;

		default:
			break;
		}
	}
	cout << endl;
}


int main()
{
	// 测试矩阵操作，所有数据按照matlab中的矩阵操作实例实现
	double a[] = {1, 2, 0,
				2, 5, -1,
				4, 10, -1};
	double b[9],c[9];
	CvMat ma, mb, mc;

	cvInitMatHeader(&ma, 3, 3, CV_64F, a, CV_AUTOSTEP);
	cvInitMatHeader(&mb, 3, 3, CV_64F, b, CV_AUTOSTEP);
	cvInitMatHeader(&mc, 3, 3, CV_64F, c, CV_AUTOSTEP);

	cout << "A = ";
	printMat(&ma);

	// 转置mb = ma'
	cvTranspose(&ma, &mb);
	cout << "A' = ";
	printMat(&mb);

	// mc = ma * mb;
	cvMatMul(&ma, &mb, &mc, 1);
	cout << "A * A' = ";
	printMat(&mc);


	// mb = inv(ma),用高斯消去法求逆
	cvInvert(&ma, &mb, CV_LU);
	cout << "inv(A) = ";
	printMat(&mb);

	// ma * inv(ma)
	cvMatMul(&ma, &mb, &mc);
	cout << "A * inv(A) = ";
	printMat(&mc);

	// mc = svd(ma),表示ma = U * mc * V'
	cvSVD(&ma, &mc, NULL, NULL, 0);		// 不返回U和V
	cout << "svd(A) = ";
	printMat(&mc);

	// mc = ma + 2;
	cvAddS(&ma, cvRealScalar(2), &mc, NULL);
	cout << "A + 2 = ";
	printMat(&mc);


	cout << endl;
	system("pause");
	return 0;
}