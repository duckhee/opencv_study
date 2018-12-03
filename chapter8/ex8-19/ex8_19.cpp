#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("../hand.jpg");
	//Mat srcImage = imread("../flower.jpg");
	if(srcImage.empty())
	{
		printf("no image file \r\n");
		return -1;
	}

	int K = 2; //# of clusters, 2, 3, 4, 
	//make color tables for displaying objects
	Mat colorTable(K, 1, CV_8UC3);
	Vec3b color;
	for(int k = 0; k < K; k++)
	{
		color[0] = rand()&180+50;
		color[1] = rand()&180+50;
		color[2] = rand()&180+50;
		colorTable.at<Vec3b>(k, 0) = color;
	}
	Mat dstImage(srcImage.size(), srcImage.type());

	int attempts = 1;
	int flags = KMEANS_RANDOM_CENTERS;
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 1.0);

	Mat samples = srcImage.reshape(3, srcImage.rows*srcImage.cols);
	samples.convertTo(samples, CV_32FC3);

	Mat labels;
	kmeans(samples, K, labels, criteria, attempts, flags);

	//display clusters using label
	for(int y = 0, k = 0; y < srcImage.rows; y++)
	{
		for(int x = 0; x < srcImage.cols; x++, k++)
		{
			//int k = y * srcImage.cols +x;
			int idx = labels.at<int>(k, 0);
			color = colorTable.at<Vec3b>(idx, 0);
			dstImage.at<Vec3b>(y, x) = color;
		}
	}
	imshow("dstImage", dstImage);
	waitKey();

	return 0;

}

