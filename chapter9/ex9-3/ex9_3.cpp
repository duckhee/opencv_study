#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("../CornerTest.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("cornertest no image\r\n");
		return -1;
	}
	int blockSize = 5;
	int ksize = 3;
	Mat eigenVal;
	cornerMinEigenVal(srcImage, eigenVal, blockSize, ksize);

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	float eval;
	for(int y = 0; y < eigenVal.rows; y++)
	{
		for(int x = 0; x < eigenVal.cols; x++)
		{
			eval = eigenVal.at<float>(y, x);

			if(eval>0.2) //corner points
			{
				circle(dstImage, Point(x, y), 5, Scalar(0, 0, 255), 2);
				cout<<"eval("<<x<<", "<<y<<") = "<<eval<<endl;
			}
		}
	}
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}

