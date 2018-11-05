#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(2, 3, CV_8UC1);
    Mat B(2,3, CV_8UC1, Scalar(0));
    Mat C(2, 3, CV_8UC3, Scalar(1, 2, 3));

    float data[] = {1, 2, 3, 4, 5, 6};
    Mat D(2, 3, CV_32FC1, data);
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;
    cout<<"D = "<<D<<endl;

    Mat A1(Size(3, 2), CV_8UC1);
    Mat B1(Size(3, 2), CV_8UC1);
    Mat C1(Size(3, 2), CV_8UC3);
    Mat D1(Size(3, 2), CV_32FC1);

    cout<<"A1 = "<<A1<<endl;
    cout<<"B1 = "<<B1<<endl;
    cout<<"C1 = "<<C1<<endl;
    cout<<"D1 = "<<D1<<endl;

    return 0;

}
