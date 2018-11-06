#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(Matx<float, 3, 3>(2, -1, 0, -1, 2, -1, 0, -1, 2));
    cout<<"A = "<<A<<endl;

    Mat B = A.t();
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;

    Mat C = A.inv(); //DECOMP_LU
    cout<<"C = "<<C<<endl;

    Mat D = A*C;
    cout<<"D = "<<D<<endl;

    Mat X(Matx<float, 3, 1>(1, 0, 0));
    Mat Y(Matx<float, 3, 1>(0, 1, 0));
    Mat Z1 = X.cross(Y);
    cout<<"Z1 = "<<Z1<<endl;
    Mat Z2 = Y.cross(X);
    cout<<"Z2 = "<<Z2<<endl;

    Mat V(Matx<float, 3, 1>(1, -1, -1));
    Mat W(Matx<float, 3, 1>(2, -1, 1));

    double dot = V.dot(W);
    cout<<"dot = "<<dot<<endl;

    Mat M1 = Mat::zeros(3, 4, CV_8U);
    Mat M2 = Mat::zeros(Size(4, 3), CV_8U);
    cout<<"M1 = "<<M1<<endl;
    cout<<"M2 = "<<M2<<endl;

    Mat M3 = Mat::ones(3, 4, CV_8U);
    Mat M4 = Mat::ones(Size(4, 3), CV_8U) * 10;
    cout<<"M3 = "<<M3<<endl;
    cout<<"M4 = "<<M4<<endl;

    Mat M5 = Mat::eye(3, 3, CV_8U);
    Mat M6 = Mat::eye(Size(3, 3), CV_8U) * 100;
    cout<<"M5 = "<<M5<<endl;
    cout<<"M6 = "<<M6<<endl;

    return 0;
}