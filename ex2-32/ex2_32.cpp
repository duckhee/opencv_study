#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(3, 3, CV_32F);
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j< A.cols; j++)
        {
            A.at<float>(i, j) = (float)(i * A.cols + j);
        }
    }
    cout<<"A = "<<A<<endl;

    Mat B = A.clone();
    cout<<"B = "<<B<<endl;

    Mat C1;
    A.copyTo(C1);
    cout<<"C1 = "<<C1<<endl;

    Mat C2;
    A.row(1).copyTo(C2);
    cout<<"C2 = "<<C2<<endl;

    Mat mask(3, 3, CV_8UC1, Scalar(0));
    mask.row(1).setTo(Scalar::all(1));
    cout<<"mask = "<<mask<<endl;

    Mat C3;
    A.copyTo(C3, mask);
    cout<<"C3 = "<<C3<<endl;

    Mat D1;
    A.convertTo(D1, CV_8U);
    cout<<"D1 = "<<D1<<endl;

    Mat D2;
    A.convertTo(D2, CV_8U, 10.0, 1.0);
    cout<<"D2 = "<<D2<<endl;

    Mat E1;
    A.assignTo(E1);
    cout<<"E1 = "<<E1<<endl;

    Mat E2;
    A.assignTo(E2, CV_8U);
    cout<<"E2 = "<<E2<<endl;

    A.setTo(Scalar::all(0));
    cout<<"A = "<<A<<endl;

    Mat F1 = A.reshape(0, 1);
    cout<<"F1 = "<<F1.size()<<"="<<F1<<endl;

    Mat F2 = A.reshape(0, 9);
    cout<<"F2 = "<<F2.size()<<"="<<F2<<endl;

    Mat F3 = A.reshape(3, 3);
    cout<<"F3 = "<<F3.size()<<"="<<F3<<endl;
}