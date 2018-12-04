#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

vector<Point2f> FindLocalMaximaF(Mat &src);

int main()
{
	Mat srcImage = imread("../CornerTest.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("no image cornertest.jpg");
		return -1;
	}

	int blockSize = 5;
	int ksize = 3;
	double k = 0.01;

	Mat R;
	cornerHarris(srcImage, R, blockSize, ksize, k);
	threshold(R, R, 0.01, 0, THRESH_TOZERO);

	vector<Point2f> cornerPoints = FindLocalMaximaF(R);
	cout<<"cornerPoints.size() = "<<cornerPoints.size()<<endl;

	Size winSize(3, 3);
	Size zeroZone(-1, -1);
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
	cornerSubPix(srcImage, cornerPoints, winSize, zeroZone, criteria);

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	vector<Point2f>::const_iterator it;
	for(it = cornerPoints.begin(); it != cornerPoints.end(); ++it)
	{
		circle(dstImage, *it, 5, Scalar(0, 0, 255), 2);
		int x = cvRound((*it).x);
		int y = cvRound((*it).y);
		float fValue = R.at<float>(y, x);
		cout<<"cornerPoints("<<(*it).x<<", "<<(*it).y<<") = "<<fValue<<endl;
	}
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}

vector<Point2f> FindLocalMaximaF(Mat &src)
{
	Mat dilated;
	Mat localMax;
	//Size size(5, 5);
	//Mat rectKernel = getStructuringElement(MORPH_RECT, size);
	dilate(src, dilated, Mat()); //local max
	//compare(src, dilated, localMax, cv::CMP_EQ);
	localMax = (src == dilated);
	//imshow("localMax", localMax);
	
	Mat eroded;
	Mat localMin;
	erode(src, eroded, Mat()); //local min
	//compare(src, eroded, localMin, CMP_GT);
	localMin = (src > eroded);
	//imshow("localMin", localMin);
	
	//bitwise_and(localMax, localMin, localMax);
	localMax = (localMax &localMin);
	//imshow("localMax = (localMax & localMin)", localMax);
	

	vector<Point2f> points;
	for(int y = 0; y < localMax.rows; y++)
	{
		for(int x = 0; x < localMax.cols; x++)
		{
			uchar uValue = localMax.at<uchar>(y, x);
			if(uValue)
			{
				points.push_back(Point2f(x, y));
			}
		}
	}
	return points;
}

