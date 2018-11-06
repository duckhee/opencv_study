#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat B(3, 3, CV_8U, 1);
    Mat C(3, 3, CV_8U, Scalar(2));

    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;

    Mat A1 = B;
    cout<<"A1 = "<<A1<<endl;

    Mat A2 = B + C;
    cout<<"A2 = "<<A2<<endl;

    B = 255;
    cout<<"B = "<<B<<endl;

    Mat D(3, 3, CV_8UC3);

    D = 255;
    cout<<"D = "<<D<<endl;
    
    D = Scalar(255, 255, 255);
    cout<<"D = "<<D<<endl;

    return 0;
}