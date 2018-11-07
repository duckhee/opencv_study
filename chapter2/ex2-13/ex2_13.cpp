#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	Scalar X = Vec4f(1, 2, 3, 4);
	Scalar Y = Scalar(10, 20, 30);
	Scalar Z = Scalar(100, 200, 300);

	cout<<"X = "<<X<<endl;
	cout<<"Y = "<<Y<<endl;
	cout<<"Z = "<<Z<<endl;

	Scalar X1 = Scalar::all(255);
	cout<<"X1 = "<<X1<<endl;
	
	Scalar X2 = X;
	cout<<"X2 = "<<(Scalar)X2<<endl;
	
	Scalar_<uchar> S1 = Scalar_<uchar>(255, 0, 0);
	cout<<"S1 = "<<S1<<endl;
	Scalar_<int> S2 = Scalar_<int>(0, 255, 0);
	cout<<"S2 = "<<S2<<endl;

	Scalar_<float> S3 = Scalar_<float>(0, 0, 255);
	cout<<"S3 = "<<S3<<endl;

	Scalar_<double> S4 = Scalar_<double>(0, 0, 255);
	cout<<"S4 = "<<S4<<endl;

	Scalar_<uchar> S5 = Scalar_<uchar>::all(255);
	cout<<"S5 = "<<S5<<endl;

	return 0;

}

