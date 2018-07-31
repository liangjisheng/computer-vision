
/*
 name: kMean.c
 func: 划分随机分布点集的K均值算法
*/

#include <stdio.h>

#include <opencv/cxcore.h>
#include <opencv/highgui.h>

void main(int argc, char **argv)
{
#define MAX_CLUSTERS 5
	CvScalar color_tab[MAX_CLUSTERS];
	IplImage *img = cvCreateImage(cvSize(500, 500), 8, 3);
	CvRNG rng = cvRNG(0xffffffff);

	color_tab[0] = CV_RGB(255, 0, 0);
	color_tab[1] = CV_RGB(0, 255, 0);
	color_tab[2] = CV_RGB(100, 100, 255);
	color_tab[3] = CV_RGB(255, 0, 255);
	color_tab[4] = CV_RGB(255, 255, 0);

	const char *lpszWin = "clusters";
	cvNamedWindow(lpszWin, 1);

	for (;;)
	{
		int k, cluster_count = cvRandInt(&rng) % MAX_CLUSTERS + 1;
		int i, sample_count = cvRandInt(&rng) % 1000 + 1;
		CvMat *points = cvCreateMat(sample_count, 1, CV_32FC2);
		CvMat *cluster = cvCreateMat(sample_count, 1, CV_32SC1);

		// generate random sample from multigaussian distribution
		for (k = 0; k < cluster_count; k++)
		{
			CvPoint center;
			CvMat point_chunk;
			center.x = cvRandInt(&rng) % img->width;
			center.y = cvRandInt(&rng) % img->height;
			cvGetRows(points, &point_chunk, k * sample_count / cluster_count,
				k == cluster_count - 1 ? sample_count : (k + 1) * sample_count / cluster_count, 1);
			cvRandArr(&rng, &point_chunk, CV_RAND_NORMAL, cvScalar(center.x, center.y, 0, 0),
				cvScalar(img->width / 6, img->height / 6, 0, 0));
		}

		// shuffle samples
		for (i = 0; i < sample_count / 2; i++)
		{
			CvPoint2D32f *pt1 = (CvPoint2D32f *)points->data.fl + cvRandInt(&rng) % sample_count;
			CvPoint2D32f *pt2 = (CvPoint2D32f *)points->data.fl + cvRandInt(&rng) % sample_count;
			CvPoint2D32f temp;
			CV_SWAP(*pt1, *pt2, temp);
		}

		cvKMeans2(points, cluster_count, cluster,
			cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
			1, 0, 0, 0, 0);
		cvZero(img);

		for (i = 0; i < sample_count; i++)
		{
			CvPoint2D32f pt = ((CvPoint2D32f *)points->data.fl)[i];
			int cluster_idx = cluster->data.i[i];
			cvCircle(img, cvPointFrom32f(pt), 2, color_tab[cluster_idx], CV_FILLED, 0, 0);
		}

		cvReleaseMat(&points);
		cvReleaseMat(&cluster);

		cvShowImage(lpszWin, img);

		int key = cvWaitKey(0);
		if (27 == key)	// ESC
			break;
	}

	getchar();
}
