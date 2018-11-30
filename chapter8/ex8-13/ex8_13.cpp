#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

typedef struct _DATA{
	Mat image;
	Mat mask;
}DATA;

void onMouse(int event, int x, int y, int flags, void *param);

int main()
{
	//Mat srcImage = imread("./flower.jpg");
	Mat srcImage = imread("./hand.jpg");
	if(srcImage.empty())
	{
		printf("no image\r\n");
		return -1;
	}
	Mat dstImage = srcImage.clone();
	imshow("dstImage", dstImage);
	Mat mask = Mat::zeros(srcImage.size(), CV_8U);
	Mat markers = Mat::zeros(srcImage.size(), CV_32S);

	DATA data = {dstImage, mask};
	setMouseCallback("dstImage", onMouse, (void *)&data);

	int mode = RETR_LIST;
	int method = CV_CHAIN_APPROX_SIMPLE;
	vector<vector<Point> > contours;

	bool bEscKey = false;
	int nKey;
	while(!bEscKey)
	{
		nKey = cvWaitKey(0);
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
				findContours(mask, contours, noArray(), mode, method);
				if(contours.size() < 1)
				{
					break;
				}
				markers = 0;
				for(int k = 0; k < contours.size(); k++)
				{
					drawContours(markers, contours, k, k+1, -1); //fill in
				}
				watershed(srcImage, markers);

				//make color tables for displaying objects
				Mat colorTable(contours.size(), 1, CV_8UC3);
				Vec3b color;
				for(int k = 0; k < contours.size(); k++)
				{
					color[0] = rand()&180+50;
					color[1] = rand()&180+50;
					color[2] = rand()&180+50;
					colorTable.at<Vec3b>(k, 0) = color;
				}
				//display objects using markers
				for(int y = 0; y < markers.rows; y++)
				{
					for(int x = 0; x < markers.cols; x++)
					{
						int k = markers.at<int>(y, x);
						if(k == -1) //boundary
						{
							color[0] = color[1] = color[2] = 255;
						}
						else if((k <= 0) || k > contours.size())
						{
							color[0] = color[1] = color[2] = 0;
						}
						else
						{
							color = colorTable.at<Vec3b>(k-1, 0);
							dstImage.at<Vec3b>(y, x) = color;
						}
					}
				}
				addWeighted(dstImage, 0.5, srcImage, 0.5, 0, dstImage);
				imshow("dstImage", dstImage);
				break;
		}
	}
	return 0;
}


void onMouse(int event, int x, int y, int flags, void *param)
{
	DATA *data = (DATA *)param;
	Mat mask = data->mask;
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


