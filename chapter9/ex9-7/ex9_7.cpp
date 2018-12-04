#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("../momentTest.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("no image\r\n");
		return -1;
	}
	Moments M = moments(srcImage, true);
	cout<<"spatial moments"<<endl;

	cout<<"M.m00 = "<<M.m00<<endl;
	cout<<"M.m10 = "<<M.m10<<endl;
	cout<<"M.m20 = "<<M.m20<<endl;
	cout<<"M.m30 = "<<M.m30<<endl;

	cout<<"M.m01 = "<<M.m01<<endl;
	cout<<"M.m11 = "<<M.m11<<endl;
	cout<<"M.m21 = "<<M.m21<<endl;
	

	cout<<"M.m02 = "<<M.m02<<endl;
	cout<<"M.m12 = "<<M.m12<<endl;
	cout<<"M.m32 = "<<M.m03<<endl;

	Point2f center;
	center.x = M.m10 / M.m00;
	center.y = M.m01 / M.m00;
	cout<<"mass center = "<<center<<endl;

	Mat dstImage;
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	circle(dstImage, center, 5, Scalar(0, 0, 255), -1);
	imshow("dstImage", dstImage);

	cout<<"central moments"<<endl;
	cout<<"M.m00 = "<<M.m00<<endl;
	cout<<"M.m10 = "<<M.m10<<endl;
	cout<<"M.m20 = "<<M.m20<<endl;
	cout<<"M.m30 = "<<M.m30<<endl;

	cout<<"M.m01 = "<<M.m01<<endl;
	cout<<"M.m11 = "<<M.m11<<endl;
	cout<<"M.m21 = "<<M.m21<<endl;

	cout<<"M.m02 = "<<M.m02<<endl;
	cout<<"M.m12 = "<<M.m12<<endl;
	cout<<"M.m03 = "<<M.m03<<endl;

	cout << "central normalized moments" << endl;
	cout << "M.nu00 = " << 1 << endl;
	cout << "M.nu10 = " << 0 << endl;
	cout << "M.nu20 = " << M.nu20 << endl;
	cout << "M.nu30 = " << M.nu30 << endl;

	cout << "M.nu01 = " << 0 << endl;
	cout << "M.nu11 = " << M.nu11 << endl;
	cout << "M.nu21 = " << M.nu21 << endl;

	cout << "M.nu02 = " << M.nu02 << endl;
	cout << "M.nu12 = " << M.nu12 << endl;
	cout << "M.nu03 = " << M.nu03 << endl;

	Mat hu;
	HuMoments(M, hu);
	cout << "Hu's 7 moments = " << endl;
	for (int i = 0; i < hu.rows; i++)
	{
		cout << "hu[" << i << "] = ";
		cout << hu.at<double>(i) << endl;
	}
	waitKey();
	return 0;
}