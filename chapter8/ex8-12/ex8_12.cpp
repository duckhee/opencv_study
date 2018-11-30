#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("./DistTest.jpg", IMREAD_GRAYSCALE); //DistTest2.jpg
	if(srcImage.empty())
	{
		printf("no image \r\n");
		return -1;
	}

	threshold(srcImage, srcImage, 200, 255, THRESH_BINARY);
	int distanceType = DIST_L1; //CV_DIST_L1
	int maskSize = 3;

	Mat distance;
	distanceTransform(srcImage, distance, distanceType, maskSize);

	Mat dstImage;
	normalize(distance, dstImage, 0, 255, NORM_MINMAX, CV_8U); 
	imshow("dstImage", dstImage);

	waitKey();

	return 0;

}
