
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

// 调试可以，直接运行不行,可能是这个摄像头的质量不行，之前那个摄像头是可以的
void test_1()
{
	// initialize and allocate memory to load the video stream from camera
	VideoCapture cam(0);
	cam.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	if(!cam.isOpened()) return ;

	while(true)
	{
		// grab and retrieve each frames of the video sequentially
		Mat3b frame;
		cam >> frame;
		imshow("Video1", frame);
		// wait for 40 milliseconds
		int c = cvWaitKey(40);

		// exit the loop if user press "Esc" key (ASCII value of "Esc" is 27)
		if(27 == c) break;
	}

	destroyWindow("Video1");
}

// 调试可以，直接运行不行
void test_2()
{
	// 0表示随机取一个摄像头
	CvCapture *cam = cvCreateCameraCapture(0);
	//double w = 320, h = 240;
	//cvSetCaptureProperty(cam, CV_CAP_PROP_FRAME_WIDTH, w);
	//cvSetCaptureProperty(cam, CV_CAP_PROP_FRAME_HEIGHT, h);
	const char szWnd[] = "windows1";
	cvNamedWindow(szWnd);
	IplImage *frame = NULL;

	while(1)
	{
		frame = cvQueryFrame(cam);
		if(!frame) break;
		cvShowImage(szWnd, frame);

		int nKey = cvWaitKey(30);
		if(27 == nKey) break;		// Esc的ASCII值为27
	}

	cvReleaseCapture(&cam);
	cvDestroyWindow(szWnd);
}

// 调试可以，直接运行不行
void test_3()
{
	VideoCapture cap(0);
	if(!cap.isOpened()) return ;
	Mat frame, edges;

	bool bStop = false;
	while(!bStop)
	{
		cap >> frame;
		// cvtColor(frame, edges, CV_BGR2GRAY);
		// GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		// Canny(edges, edges, 0, 30, 3);
		imshow("test", frame);
		if(27 == waitKey(30))
			bStop = true;
	}

	destroyWindow("test");
}

// 调试可以，直接运行不行
void test_4()
{
	CvCapture *capture = cvCreateCameraCapture(0);
	IplImage *frame = NULL;
	const char szName[] = "win";
	cvNamedWindow(szName);

	while(1)
	{
		frame = cvQueryFrame(capture);
		if(!frame) break;

		IplImage* out = cvCreateImage(cvGetSize(frame), frame->depth, 1);
		cvCanny(frame, out, 10, 100, 3);
		cvShowImage(szName, out);

		char c = cvWaitKey(30);
		if(27 == c) break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow(szName);
}

void test_5_write()
{
	VideoCapture cap(0);
	double rate = 25.0;			// 视频的帧率
	Size videoSize(1280, 960);
	VideoWriter writer("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, videoSize);
	Mat frame;

	while(cap.isOpened())
	{
		cap >> frame;
		writer << frame;
		imshow("video", frame);
		if(waitKey(30) == 27) break;
	}

	destroyWindow("video");
}

void test_6()
{
	CvCapture *cam = cvCaptureFromCAM(0);
	if(!cam)
	{
		cout << "Could not initialize opening of Camera 0..\n";
		system("pause");
		return ;
	}

	cvNamedWindow("win", CV_WINDOW_AUTOSIZE);
	while(1)
	{
		IplImage *frame = cvQueryFrame(cam);
		if(!frame) break;
		cvShowImage("win", frame);
		int nRet = cvWaitKey(30);

		if(nRet == (int)'s')
		{
			// time_t t;
			// time(&t);
			time_t timer = time(NULL);
			struct tm *tblock;
			tblock = localtime(&timer);
			char szTime[128] = {0};
			sprintf(szTime, "%d", timer);
			strcat(szTime, ".jpg");
			cvSaveImage(szTime, frame);
		}

		if(27 == nRet) break;
	}

	cvReleaseCapture(&cam);
	cvDestroyWindow("win");
}

// 获取摄像头的id
//int listDevices(vector<string> &list)
//{
//	//COM Library Initialization  
//	//comInit();  
//
//	//if (!silent)printf("\nVIDEOINPUT SPY MODE!\n\n");  
//
//	ICreateDevEnum *pDevEnum = NULL;
//	IEnumMoniker *pEnum = NULL;
//	int deviceCounter = 0;
//	CoInitialize(NULL);
//	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
//		CLSCTX_INPROC_SERVER, IID_ICreateDevEnum,
//		reinterpret_cast<void**>(&pDevEnum));
//
//	if(SUCCEEDED(hr))
//	{
//		// Create an enumerator for the video capture category.
//		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
//		if(S_OK == hr)
//		{
//			 //if (!silent)printf("SETUP: Looking For Capture Devices\n");  
//			IMoniker *pMoniker = NULL;
//			while(pEnum->Next(1, &pMoniker, NULL) == S_OK)
//			{
//				IPropertyBag *pPropBag;
//				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)(&pPropBag));
//				if(FAILED(hr))
//				{
//					pMoniker->Release();
//					continue;		// Skip this one, maybe the next one will work.
//				}
//
//				// Find the description or friendly name
//				VARIANT varName;
//				VariantInit(&varName);
//				hr = pPropBag->Read(L"Description", &varName, 0);
//				if(FAILED(hr))
//					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
//
//				if(SUCCEEDED(hr))
//				{
//					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
//					int count = 0;
//					char tmp[255] = {0};
//					// int maxLen = sizeof(deviceNames[0]) / sizeof(deviceNames[0][0]) - 2;
//					while(varName.bstrVal[count] != 0x00 && count < 255)
//					{
//						tmp[count] = (char)varName.bstrVal[count];
//						count++;
//					}
//					list.push_back(tmp);
//					//deviceNames[deviceCounter][count] = 0;  
//
//					//if (!silent)printf("SETUP: %i) %s \n", deviceCounter, deviceNames[deviceCounter]);
//				}
//
//				pPropBag->Release();
//				pPropBag = NULL;
//
//				pMoniker->Release();
//				pMoniker = NULL;
//
//				deviceCounter++;
//			}
//
//			pDevEnum->Release();
//			pDevEnum = NULL;
//
//			pEnum->Release();
//			pEnum = NULL;
//		}
//
//		//if (!silent)printf("SETUP: %i Device(s) found\n\n", deviceCounter); 
//	}
//
//	// comUnInit();
//	return deviceCounter;
//}


int main()
{
	// test_1();
	// test_2();
	// test_3();
	// test_4();
	// test_5_write();
	test_6();

	system("pause");
	return 0;
}