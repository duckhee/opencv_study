#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(2, 3, CV_32F);
    
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A.at<float>(i, j) = (float)(i*A.cols + j);
        }
    }

    Mat_<float> B = (Mat_<float>)A;
    Mat_<float> &C = (Mat_<float> &)A;

    B(0, 0) = 10.0f;
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;

    Mat_<float> D1(2, 3);
    for(int i = 0; i <D1.rows; i++)
    {
        for(int j = 0; j < D1.cols; j++)
        {
            D1(i, j) = (float)(i * D1.cols + j);
        }
    }
    cout<<"D1 = "<<D1<<endl;

    Mat_<float> D2(2, 3, 10);
    cout<<"D2 = "<<D2<<endl;

    Mat_<float> E1 = (Mat_<float>(2, 3)<<1, 2, 3, 4, 5, 6);
    Mat E2 = (Mat_<float>(2, 3)<<1, 2, 3, 4, 5, 6);
    cout<<"E1 = "<<E1<<endl;
    cout<<"E2 = "<<E2<<endl;

    return 0;

}