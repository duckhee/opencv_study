#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

vector<Point> FindLocalMaxima(Mat &src);

int main()
{
	Mat srcImage = imread("../CornerTest.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("no image\r\n");
		return -1;
	}
	Mat cornerMap;
	preCornerDetect(srcImage, cornerMap, 3);

	cornerMap = abs(cornerMap);
	threshold(cornerMap, cornerMap, 0.01, 0, THRESH_TOZERO);

	vector<Point> cornerPoints = FindLocalMaxima(cornerMap);
	cout<<"cornerPoints.size() = "<<cornerPoints.size()<<endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	vector<Point>::const_iterator it;
	for(it = cornerPoints.begin(); it != cornerPoints.end(); ++it)
	{
		circle(dstImage, *it, 5, Scalar(0, 0, 255),2);
	}
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}

vector<Point> FindLocalMaxima(Mat &src)
{
	Mat dilated;
	Mat localMax;
	Size size(11, 11);
	Mat rectKernel = getStructuringElement(MORPH_RECT, size);

	dilate(src, dilated, rectKernel); //local max, if Mat()->3x3
	//compare(src, dilated, localMax, CMP_EQ);
	localMax = (src == dilated);
	//imshow("localMax", localMax);
	

	Mat eroded;
	Mat localMin;
	erode(src, eroded, rectKernel); //local min, if Mat()->3x3
	//compare(src, eroded, localMin, CMP_GT);
	localMin = (src>eroded);
	//imshow("localMin", localMin);
	
	//bitwisze_and(localMax, localMin, CMP_GT);
	localMax = (localMax & localMin);
	//imshow("localMax=(localMax & localMin)", locaMax);
	

	vector<Point> points;
	for(int y = 0; y < localMax.rows; y++)
	{
		for(int x = 0; x < localMax.cols; x++)
		{
			uchar uValue = localMax.at<uchar>(y, x);
			if(uValue)
			{
				points.push_back(Point(x, y));
			}
		}
	}
	return points;
}

