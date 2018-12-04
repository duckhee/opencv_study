#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("../CornerTest.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("no image \r\n");
		return -1;
	}

	int maxCorners = 8;
	double qualityLevel = 0.001;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = true; //flase
	double k = 0.04;

	vector<Point>cornerPoints;
	goodFeaturesToTrack(srcImage, cornerPoints, maxCorners, qualityLevel, minDistance, noArray(), blockSize, useHarrisDetector, k);
	cout<<"cornerPoints.size() = "<<cornerPoints.size()<<endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	vector<Point>::const_iterator it;
	for(it = cornerPoints.begin(); it != cornerPoints.end(); ++it)
	{
		circle(dstImage, *it, 5, Scalar(0, 0, 255), 2);
		cout<<"cornerPoints("<<(*it).x<<", "<<(*it).y<<")"<<endl;
	}
	imshow("dstImage", dstImage);

	waitKey();

	return 0;

}

