#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("./ContourTest.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("no image \r\n");
		return -1;
	}

	threshold(srcImage, srcImage, 128, 255, THRESH_BINARY);

	Mat srcImage2 = srcImage.clone();
	Mat dstImage(srcImage2.size(), CV_8UC3);
	cvtColor(srcImage2, dstImage, COLOR_GRAY2BGR);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//int mode = RETR_CCOMP;
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;

	findContours(srcImage, contours, hierarchy, mode, method);
	cout<<"contours.size() = "<<contours.size()<<endl;

	//drawContours(dstImage, contours, -1, Scalar(2, 0, 255), 4, 8, hierarchy, 3); //maxLevel = 0, 1, 2, 3
	//imshow("dstImage, dstImage);
	//waitKey();
	
	Scalar color[4] = {Scalar(255, 0, 0), //next
		Scalar(0, 255, 0), //previous
		Scalar(255, 0, 255), //the first child
		Scalar(0, 255, 255) //parent
	};

	for(int k = 0; k < contours.size(); k++)
	{
		cvtColor(srcImage2, dstImage, COLOR_GRAY2BGR);
		cout<<"hierarchy["<<k<<"][0] = "<<hierarchy[k][0]<<endl;
		cout<<"hierarchy["<<k<<"][1] = "<<hierarchy[k][1]<<endl;
		cout<<"hierarchy["<<k<<"][2] = "<<hierarchy[k][2]<<endl;
		cout<<"hierarchy["<<k<<"][3] = "<<hierarchy[k][3]<<endl;

		drawContours(dstImage, contours, k , Scalar(0, 0, 255), 2);
		for(int j = 0; j < 4; j++)
		{
			if(hierarchy[k][j] < 0)
			{
				continue;
			}
			drawContours(dstImage, contours, hierarchy[k][j], color[j], 2);
		}
		imshow("dstImage", dstImage);
		waitKey();
	}
	return 0;
}
