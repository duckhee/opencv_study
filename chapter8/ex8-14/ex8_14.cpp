#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define TH 10 //for heart10.jpg
//#define TH 40 //for circle.jpg


int main()
{
	Mat srcImage = imread("./heart10.jpg");
	//Mat srcImage = imread("./circle.jpg");
	if(srcImage.empty())
	{
		printf("no image \r\n");
		return -1;
	}
	imshow("srcImage", srcImage);

	Mat srcImage8;
	cvtColor(srcImage, srcImage8, CV_BGR2GRAY);

	Mat dstImage8;
	threshold(srcImage8, dstImage8, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
	imshow("dstImage8", dstImage8);

	//find marker by using distanceTransform and threshold
	Mat distance, distImage8;
	distanceTransform(dstImage8, distance, CV_DIST_L1, 3);
	normalize(distance, distImage8, 0, 255, NORM_MINMAX, CV_8U);
	imshow("distance", distImage8);

	Mat mask;
	//threshold(dstImage8, mask, TH, 255, THRESH_BINARY);
	mask = distance > TH;
	imshow("mask", mask);

	vector<vector<Point> > contours;
	findContours(mask, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	if(contours.size() < 1)
	{
		return 0;
	}
	Mat markers = Mat::zeros(srcImage.size(), CV_32S);
	//marker = 0;
	for(int k = 0; k < contours.size(); k++)
	{
		drawContours(markers, contours, k, k+1, -1); //fill in
	}
	//create a background marker
	circle(markers, Point(5, 5), 3, Scalar::all(contours.size()+1), -1);

	//segment object by using markers
	Mat dstImage = srcImage.clone();
	watershed(dstImage, markers);

	//make color tables for displaying objects
	Mat colorTable(contours.size()+1, 1, CV_8UC3);
	Vec3b color;
	for(int k = 0; k < contours.size() + 1; k++)
	{
		color[0] = theRNG().uniform(0, 180) + 50;
		color[1] = theRNG().uniform(0, 180) + 50;
		color[2] = theRNG().uniform(0, 180) + 50;
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
				color[0] = color[1]=color[2]=255;
			}
			else if(k <= 0 || k > contours.size() + 1)
			{
				color[0]=color[1]=color[2]=0;
			}
			else
			{
				color = colorTable.at<Vec3b>(k-1, 0);
				dstImage.at<Vec3b>(y, x) = color;
			}
		}
	}
	addWeighted(dstImage, 0.5, srcImage, 0.5, 0, dstImage);
	imshow("dstImage", dstImage);;
	waitKey();

	return 0;

}
