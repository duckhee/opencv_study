#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("no image\r\n");
		return -1;
	}

	Mat pyrImageD[3];
	pyrImageD[0] = srcImage.clone();
	imshow("pryImageD[0]", pyrImageD[0]);
	cout<<"pyrImageD[0].size() = "<<pyrImageD[0].size()<<endl;

	pyrDown(pyrImageD[0], pyrImageD[1]);
	imshow("pyrImageD[1]", pyrImageD[1]);
	cout<<"pyrImageD[1].size() = "<<pyrImageD[1].size()<<endl;

	pyrUp(pyrImageD[0], pyrImageD[2]);
	imshow("pyrImageD[2]", pyrImageD[2]);
	cout<<"pyrImageD[2] = "<<pyrImageD[2].size()<<endl;

	Mat pyrImageU[2];
	pyrUp(pyrImageD[1], pyrImageU[0]);
	imshow("pyrImageU[0]", pyrImageU[0]);
	cout<<"pyrImageU[0].size() = "<<pyrImageU[0].size()<<endl;

	pyrUp(pyrImageD[2], pyrImageU[1]);
	imshow("pyrImageU[1]", pyrImageU[1]);
	cout<<"pyrImageU[1].size() = "<<pyrImageU[1].size()<<endl;

	waitKey();

	return 0;

}
			
