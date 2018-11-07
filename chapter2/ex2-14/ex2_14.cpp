#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Matx33f A(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat B(A);
    cout<<"B = "<<B<<endl;

    cout<<"B[0:1, 0:3] = "<<B(Range(0, 1), Range(0,3))<<endl;
    cout<<"B[0:2, 0:3] = "<<B(Range(0, 2), Range(0,3))<<endl;
    cout<<"B[1:2, 0:3] = "<<B(Range(1, 2), Range(0,3))<<endl;

    Mat C = B(Range(1, 3), Range::all());
    cout<<"C = "<<C<<endl;

    Mat D = B(Range::all(), Range(1, 3));
    cout<<"D = "<<D<<endl;

    B(Range(0,1), Range::all()).copyTo(B(Range(1, 2), Range::all()));
    cout<<"B = "<<B<<endl;
    return 0;
}