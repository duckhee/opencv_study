#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(1, 3, CV_8U);
    int a = -1;
    float b = 2.6;
    double c = 300.4;

    A.at<uchar>(0, 0) = a;
    A.at<uchar>(0, 1) = b;
    A.at<uchar>(0, 2) = c;
    cout<<"A"<<A<<endl<<endl;

    cout<<"saturate_cast<uchar>"<<endl;
    A.at<uchar>(0, 0) = saturate_cast<uchar>(a);
    A.at<uchar>(0, 1) = saturate_cast<uchar>(b);
    A.at<uchar>(0, 2) = saturate_cast<uchar>(c);
    cout<<"A"<<A<<endl<<endl;

    return 0;

}