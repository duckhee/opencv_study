#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<uchar> A(10, 10);

    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A(i, j) = (uchar)(i * A.cols + j);
        }
    }
    cout<<"A = "<<A<<endl;

    Mat_<uchar> B = A(Range(5, 8), Range(3, 6));
    cout<<"B = "<<B<<endl;

    Mat_<uchar> C = B.adjustROI(1, 1, 1, 1);
    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;

    Mat D = A(Rect(0, 0, 5, 5));
    cout<<"D = "<<D<<endl;

    Range ranges[2] = {Range(5, 8), Range(3, 6)};
    Mat E = A(ranges);
    cout<<"E = "<<E<<endl;

    return 0;

}