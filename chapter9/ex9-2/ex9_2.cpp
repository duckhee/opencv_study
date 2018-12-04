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
	
	int blockSize = 5;
	int ksize = 3;
	Mat cornerMap;
	cornerEigenValsAndVecs(srcImage, cornerMap, blockSize, ksize);

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	Vec6f element;
	for(int y = 0; y < cornerMap.rows; y++)
	{
		for(int x = 0; x < cornerMap.cols; x++)
		{
			element = cornerMap.at<Vec6f>(y, x);

			if(element[0]>0.2 && element[1]>0.2) //corner points
			{
				circle(dstImage, Point(x, y), 5, Scalar(0, 0, 255), 2);
				cout<<"eval("<<x<<", "<<y<<") = "<<element[0]<<", "<<element[1]<<endl;
			}
			if(element[0]>0.2) //edges
			{
				circle(dstImage, Point(x, y), 1, Scalar(255, 0, 0), 1);
			}

		}
	}
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}

