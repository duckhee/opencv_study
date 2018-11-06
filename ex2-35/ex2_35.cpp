#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(10, 10, CV_32F);

    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A.at<float>(i, j) = (float)(i * A.cols + j);
        }
    }
    cout<<"A = "<<A.size()<<"="<<A<<endl;

    Mat B = A(Range(5, 8), Range(3, 6));
    cout<<"B = "<<B<<endl;

    Mat C = A(Rect(0, 0, 5, 5));
    cout<<"C = "<<C<<endl;

    Range ranges[2] = {Range(5, 8), Range(3, 6)};
    Mat D = A(ranges);
    cout<<"D = "<<D<<endl;

    CvMat E = D;
    cout<<"E = "<<cvarrToMat(&E)<<endl;
    //cout<<"E = "<<Mat(&E)<<endl; //opnecv 2.4.13

    IplImage F = D;
    cout<<"F = "<<cvarrToMat(&F)<<endl;
    //cout<<"F = "<<Mat(&F)<<endl; //opnecv 2.4.13

    return 0;
}