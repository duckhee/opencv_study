#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void Printmat(const char *strName, Mat A);

int main()
{
	uchar dataA[] = {
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0, 
		0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0, 
		0, 1, 1, 1, 1, 1, 0, 
		0, 0, 0, 0, 0, 0, 0
	};
	Mat A(7, 7, CV_8U, dataA);
	Printmat("A = ", A);

	int distanceType = DIST_L1; //CV_DIST_L1
	int maskSize = 5;
	Mat labels;
	Mat distance;
	//distanceTransform(A, distance, distanceType, maskSize);
	//distanceTransform(A, distance, labels, distanceType, maskSize, DIST_LABEL_CCOMP);
	distanceTransform(A, distance, labels, distanceType, maskSize, DIST_LABEL_PIXEL);
	Printmat("distance = ", distance);
	Printmat("labels = ", labels);

	waitKey();

	return 0;
}

void Printmat(const char *strName, Mat A)
{
	int x, y;
	uchar uValue;
	float fValue;
	double dValue;
	int iValue;

	cout<<endl<<endl<<strName<<endl;
	cout<<setiosflags(ios::fixed);
	for(y = 0; y < A.rows; y++)
	{
		for(x = 0; x < A.cols; x++)
		{
			switch(A.type())
			{
				case CV_8U:
					uValue = A.at<uchar>(y, x);
					cout<<setw(4)<<(int)uValue;
				break;
				case CV_32S:
					iValue = A.at<int>(y, x);
					cout<<setw(4)<<iValue;
				break;
				case CV_32F:
					fValue = A.at<float>(y, x);
					cout<<setprecision(1)<<setw(5)<<fValue;
				break;
				case CV_64F:
					dValue = A.at<double>(y, x);
					cout<<setprecision(1)<<setw(5)<<dValue;
				break;
			}
		}
		cout<<endl;
	}
	cout<<endl;
}

