#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(3, 3, CV_32F);
    for(int i =0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A.at<float>(i, j) = (float)(i * A.cols + j);
        }
    }

    Mat B = A.row(0);
    Mat C = A.col(0);
    Mat D = A.rowRange(0, 2);
    Mat E = A.colRange(0, 2);

    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;
    cout<<"D = "<<D<<endl;
    cout<<"E = "<<E<<endl;

    A.row(0) = A.row(0) * 10;
    A.row(1) = A.row(1) * 100;
    A.row(2) = A.row(2) * 1000;
    cout<<"A = "<<A<<endl;

    A.row(1) = A.row(2); //not work
    cout<<"A = "<<A<<endl;

    A.row(2).copyTo(A.row(1));
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;
    cout<<"D = "<<D<<endl;
    cout<<"E = "<<E<<endl;

    return 0;
}