
/*
 name: invImage.c
 func: 读取图像文件，先进行图像反转，将反转后的图像显示在屏幕上
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char *argv[])
{
	IplImage *img = NULL;
	int height, width, step, channels;
	uchar *data;
	int i, j, k;
	if (argc < 2)
	{
		printf("Usage: %s ImageFileName\n", argv[0]);
		exit(0);
	}

	img = cvLoadImage(argv[1], 1);
	if (NULL == img)
	{
		printf("Could not load image file: %s\n", argv[1]);
		exit(0);
	}

	// get image info
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;
	printf("Processing a %dx%d image with %d channels\n", height, width, channels);

	const char *lpszWinName = "mainWin";
	cvNamedWindow(lpszWinName, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(lpszWinName, 100, 100);

	// 反转图像
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			for (k = 0; k < channels; k++)
				data[i * step + j * channels + k] = 255 - data[i * step + j * channels + k];

	cvSaveImage("inv.jpg", img, 0);
	cvShowImage(lpszWinName, img);
	cvWaitKey(0);
	cvReleaseImage(&img);

	getchar();
	return 0;
}
