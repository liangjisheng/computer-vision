#include <cv.h>
#include <highgui.h>
#include <iostream.h>

int* value=0;
int count=100;

void track_call_back(int pos)
{
	cout<<pos<<" ";
}

int main()
{

	cvNamedWindow("test",CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Bar","test",value,count,track_call_back);
	while(1)
	{
		if(27==cvWaitKey(27))
			break;
	}
	cvDestroyWindow("test");
	return 0;
  
}