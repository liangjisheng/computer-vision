
#include <iostream>
#include <cstdlib>
#include <cmath>

#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main()
{
	IplImage* img = 0;
	int height, width, step, channels;
	uchar* data;
	int i,j,k;

	img = cvLoadImage("D:\\InstallSoftware\\JPG\\1.jpg");
	if(!img)
	{
		cout << "Could not load image file." << endl;
		exit(0);
	}

	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar*)img->imageData;

	cout << "Processing a " << width << " x " << height
		<< " image with " << channels << " channels" << endl;

	cvNamedWindow("main", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("main", 100, 100);

	// 反转图像
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			for(k = 0; k < channels; k++)
			{
				data[i * step + j * channels + k] = 
					255 - data[i * step + j * channels + k];
			}
		}
	}

	cvShowImage("main", img);
	cvWaitKey(0);
	cvReleaseImage(&img);

	system("pause");
	return 0;
}