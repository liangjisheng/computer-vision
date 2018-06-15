// opencv矩阵
#include <iostream>
#include "cv.h"
#include "highgui.h"

using std::cout;
using std::endl;

// 累加一个三通道矩阵中的所有元素
float Sum(const CvMat* mat)
{
	float s = 0.0f;
	for(int row = 0; row < mat->rows; row++)
	{
		const float* ptr = (const float*)(mat->data.ptr + row * mat->step);
		for(int col = 0; col < mat->cols; col++)
			s += *ptr++;		// 先解引用，然后移向下一个字节
	}
	return s;
}

int main()
{
	float vals[] = { 0.866025, -0.500000, 0.500000, 0.866025};
	CvMat rotmat;
	cvInitMatHeader(&rotmat, 2, 2, CV_32FC1, vals);

	CvMat* mat = cvCreateMat(5, 5, CV_32FC1);
	// 获取矩阵元素，利用宏CV_MAT_ELEM
	float element_3_2 = CV_MAT_ELEM(*mat, float, 3, 2);

	// 返回索引的指针
	float ele_3_2 = 7.7;
	*((float*)CV_MAT_ELEM_PTR(*mat, 3, 2)) = ele_3_2;

	system("pause");
	return 0;
}