#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

typedef struct _DATA{
	Mat image;
	Mat mask;
}DATA;

void onMouse(int event, int x, int y, int flags, void *params);

int main()
{
	Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("../lena.jpg");
	if(srcImage.empty())
	{
		printf("no image\r\n");
		return -1;	
	}

	Mat dstImage = srcImage.clone();
	Mat mask = Mat::zeros(srcImage.size(), CV_8U);
	imshow("dstImage", dstImage);

	DATA data = {dstImage, mask};
	setMouseCallback("dstImage", onMouse, (void *)&data);

	double inpainRadius = 5;
	//int flags = INPAINT_NS;
	int flags = INPAINT_TELEA;

	bool bEscKey = false;
	int nKey;
	while(!bEscKey)
	{
		nKey = waitKey(0);
		switch(nKey)
		{
			case 27:
				bEscKey = true;
			break;
			case 'r':
				mask = 0;
				srcImage.copyTo(dstImage);
				imshow("dstImage", dstImage);
			break;
			case ' ':
				inpaint(dstImage, mask, dstImage, inpainRadius, flags);
				imshow("dstImage", dstImage);
			break;
		}
	}
	return 0;
}


void onMouse(int event, int x, int y, int flags, void *params)
{
	DATA *data = (DATA *)params;
	Mat mask = data->image;
	Mat dstImage = data->image;
	switch(event)
	{
		case EVENT_MOUSEMOVE:
			if(flags & EVENT_FLAG_LBUTTON)
			{
				circle(mask, Point(x, y), 10, Scalar::all(255), -1);
				circle(dstImage, Point(x, y), 10, Scalar::all(255), -1);
			}
	}
	imshow("dstImage", dstImage);
}


