#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void floodFillPostprocess(Mat &img, const Scalar &colorDiff);

int main()
{
	//Mat srcImage = imread("../segmentTest.jpg");
	Mat srcImage = imread("../lena.jpg");
	if(srcImage.empty())
	{
		printf("no image \r\n");
		return -1;
	}
	int maxLevel = 4;
	double sp = 10;
	double sr = 40;

	Mat dstImage;
	pyrMeanShiftFiltering(srcImage, dstImage, sp, sr, maxLevel);
	floodFillPostprocess(dstImage, Scalar::all(2));
	imshow("srcImage", srcImage);
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}

//sources/sample/cpp/meanshift_segmentation.cpp
void floodFillPostprocess(Mat &img, const Scalar &colorDiff = Scalar::all(1))
{
	RNG rng = theRNG();
	Mat mask(img.rows + 2, img.cols + 2, CV_8U, Scalar::all(0));
	for(int y = 0; y < img.rows; y++)
	{
		for(int x = 0; x < img.cols; x++)
		{
			if(mask.at<uchar>(y+1, x+1) == 0)
			{
				Scalar newVal(rng(256), rng(256), rng(256));
				floodFill(img, mask, Point(x, y), newVal, 0, colorDiff, colorDiff);
			}
		}
	}
}

