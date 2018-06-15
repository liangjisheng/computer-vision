
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <Windows.h>

#include <highgui.h>
#include <cv.h>

using namespace std;
using namespace cv;


void printMat(CvMat* arr);
void GenRandn(CvMat* arr, int seed);		// 生成标准正态分布的随机矩阵
void GenRand(CvMat* arr, int seed);			// [0, 1]均匀分布的随机矩阵
// 比较函数
static int cmp_func(const void* _a, const void* _b, void * userdata);

void testMultiply();						// 测试矩阵乘法
void test_cvGetRawData();					// 将缓存数据填入CvMat数组中
void testDCT();								// 计算DCT变换
void testRand();							// 生成随机数
void testSeqSort();							// 二维序列排序


int main()
{
	testMultiply();
	cout << endl;

	test_cvGetRawData();
	cout << endl;

	testDCT();
	cout << endl;

	testRand();
	cout << endl;

	testSeqSort();
	cout << endl;

	system("pause");
	return 0;
}


void testMultiply()
{
	double a[] = {1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 11, 12};
	double b[] = {1, 5, 9,
				2, 6, 10,
				3, 7, 11,
				4, 8, 12};

	double c[9] = {0};
	CvMat ma, mb, mc;
	cout << "\n=== Test multiply ===" << endl;
	
	cvInitMatHeader(&ma, 3, 4, CV_64FC1, a, CV_AUTOSTEP);
	cvInitMatHeader(&mb, 4, 3, CV_64FC1, b, CV_AUTOSTEP);
	cvInitMatHeader(&mc, 3, 3, CV_64FC1, c, CV_AUTOSTEP);

	cvMatMulAdd(&ma, &mb, 0, &mc);

	cout << "ma:" << endl;
	printMat(&ma);
	cout << "mb:" << endl;
	printMat(&mb);
	cout << "mc:" << endl;
	printMat(&mc);
}


void printMat(CvMat* arr)
{
	int i, j;
	for(i = 0; i < arr->rows; i++)
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


void test_cvGetRawData()
{
	float* data;
	int step;						// 表示每行数据的长度
	float a[] = {1, 2, 3, 4,
				-5, 6, 7, 8,
				9, -10, -11, 12};
	CvMat arr;
	CvSize size;
	int x, y;

	cout << "\n=== Test get raw data ===" << endl;
	cvInitMatHeader(&arr, 3, 4, CV_32FC1, a, CV_AUTOSTEP);
	cvGetRawData(&arr, (uchar**)&data, &step, &size);
	step /= sizeof(data[0]);

	cout << "\nCvMat = ";
	printMat(&arr);
	cout << "\nData = ";
	for(y = 0; y < size.height; y++, data += step)
	{
		cout << endl;
		for(x = 0; x < size.width; x++)
		{
			data[x] = (float)fabs(data[x]);
			cout << setprecision(2) << setw(8) << data[x];
		}
	}
	cout << endl;
}


void testDCT()
{
	float data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	CvMat a;
	a = cvMat(2, 4, CV_32FC1, data);
	cout << "\n=== Test DCT ===";
	cout << "\nOriginal matrix = ";
	printMat(&a);

	cvDCT(&a,&a, CV_DXT_FORWARD);
	cout << "\n2-D DCT = ";
	printMat(&a);

	cvDCT(&a, &a, CV_DXT_INVERSE);
	cout << "\n2-D IDCT = ";
	printMat(&a);
}


void testRand()
{
	CvMat* a = cvCreateMat(10, 6, CV_32F);
	cout << "\n=== Test generating random matrix ===" << endl;
	cout << "\nGenRandn\n";

	for(int i = 0; i < 5; i++)
	{
		GenRandn(a, i);
		printMat(a);
	}

	cout << "\nGenRand\n";
	for(int i = 0; i < 5; i++)
	{
		GenRand(a, i);
		printMat(a);
	}

	cvReleaseMat(&a);
}


void GenRand(CvMat* arr, int seed)
{
	CvRandState rng;
	rng.state = cvRNG(0xffffffff);		// Initialize random generator
	cvRandInit(&rng,
		0, 1,			// use dummy parameters now and adjust them further
		seed,			// use input seed here
		CV_RAND_UNI);	// specify uniform type

	cvRandArr(&rng.state, arr, CV_RAND_UNI, cvRealScalar(0), cvRealScalar(1));
	// RNG state does not need to be deallocated
}


void GenRandn(CvMat* arr, int seed)
{
	CvRandState rng;
	rng.state = cvRNG(0xffffffff);
	cvRandInit(&rng,
		0, 1,
		seed,
		CV_RAND_NORMAL);

	// fill random numbers to arr, with mean zero and variance one
	cvRandArr(&rng.state, arr, CV_RAND_NORMAL,
		cvRealScalar(0), cvRealScalar(1));
	// RNG state does not need to be deallocated
}


void testSeqSort()
{
	// Sort 2D points in top-to-bottom, left-to-right order
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* seq = cvCreateSeq(CV_32SC2, sizeof(CvSeq), sizeof(CvPoint), storage);
	cout << "\n=== Test sequence sorting ===\n";

	for(int i = 0; i < 10;i ++)
	{
		CvPoint pt;
		pt.x = rand() % 1000;
		pt.y = rand() % 1000;
		cvSeqPush(seq, &pt);
	}

	cout << "\nOriginal point set: \n";
	for(int i = 0; i < seq->total; i++)
	{
		CvPoint* pt = (CvPoint*)cvGetSeqElem(seq, i);
		cout << "(" << pt->x << "," << pt->y << ")" << endl;
	}

	cvSeqSort(seq, cmp_func, 0);

	cout << "\nAfter sorting:\n";
	for(int i = 0; i < seq->total; i++)
	{
		CvPoint* pt = (CvPoint*)cvGetSeqElem(seq, i);
		cout << "(" << pt->x << "," << pt->y << ")" << endl;
	}

	cvClearSeq(seq);
	cvReleaseMemStorage(&storage);
}


static int cmp_func(const void* _a, const void* _b, void * userdata)
{
	CvPoint* a = (CvPoint*)_a;
	CvPoint* b = (CvPoint*)_b;
	int y_diff = a->y - b->y;
	int x_diff = a->x - b->x;
	// 排序时，y的优先级比x的优先级高
	return y_diff ? y_diff : x_diff;
}


