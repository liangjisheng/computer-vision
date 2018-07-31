#include "cv.h"
#include "highgui.h"

void my_mouse_callback(int event,int x,int y,int flage,void* param);
CvRect box;
bool   Draw_box=false;
void draw_box(IplImage * img,CvRect rect)
{
	cvRectangle(img,cvPoint(box.x,box.y),cvPoint(box.x+box.width,box.y+box.height),cvScalar(255,255,255));
}

int main( int argc, char** argv )
{
	box=cvRect(-1,-1,0,0);
	IplImage  *imge=cvCreateImage(cvSize(200,200),IPL_DEPTH_8U,3);
	cvZero(imge);
	IplImage* temp=cvCloneImage(imge);
	cvNamedWindow("box_windows",0);
	cvResizeWindow("box_windows",500,500);
	cvMoveWindow("box_windows",500,500);
	cvSetMouseCallback("box_windows",my_mouse_callback,(void*)imge);
	while(1)
	{
		cvCopyImage(imge,temp);
		if(Draw_box)
		{
			draw_box(temp,box);
		}
		cvShowImage("box_windows",temp);
		if(27==cvWaitKey(15))
			break;
	}
	cvReleaseImage(&temp);
	cvReleaseImage(&imge);
	cvDestroyWindow("box_windows");
	return 0;
}

void my_mouse_callback(int event,int x,int y,int flage,void* param)
{
	IplImage* image=(IplImage*)param;
	switch(event)
	{
	case CV_EVENT_MOUSEMOVE:
		{
			if(Draw_box)
			{
				box.width=x-box.x;
				box.height=y-box.y;
			}
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		{
			Draw_box=true;
			box=cvRect(x,y,0,0);
		}
		break;
	case CV_EVENT_LBUTTONUP:
		{
			Draw_box=false;
			if(box.width<0)
			{
				box.x+=box.width;
				box.width*=-1;
			}
			if(box.height<0)
			{
				box.y+=box.height;
				box.height*=-1;
			}
			draw_box(image,box);
		}
		break;
	}

}

