#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat dstImage(Size(512, 512), CV_8UC3, Scalar::all(255));
	
	rectangle(dstImage, Point(50, 50), Point(200, 200), Scalar(0, 0, 255), 2);
	circle(dstImage, Point(300, 300), 100, Scalar(0, 0, 255),2);

	Scalar loDiff = Scalar::all(10);
	Scalar upDiff = Scalar::all(10);
	int floodFlags = 8 | FLOODFILL_FIXED_RANGE;
	Rect boundRect;

	//fill in the rectangle
	floodFill(dstImage, Point(100, 100), Scalar(255, 0, 0), &boundRect, loDiff, upDiff, floodFlags);
	rectangle(dstImage, boundRect, Scalar(0, 255, 0), 2);

	//fill in the circle
	floodFill(dstImage, Point(300, 300), Scalar(255, 0, 0), &boundRect, loDiff, upDiff, floodFlags);
	rectangle(dstImage, boundRect, Scalar(0, 255, 0), 2);

	imshow("dstImage", dstImage);
	waitKey();

	return 0;

}
