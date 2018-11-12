#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A1(3, 3, CV_32F);
    setIdentity(A1);
    cout<<"A1 = "<<A1<<endl;

    Mat A2(3, 3, CV_32F);
    setIdentity(A2, 5);
    cout<<"A2 = "<<A2<<endl;

    Mat A3 = Mat::eye(3, 3, CV_32F) * 5;
    cout<<"A3 = "<<A3<<endl;

    float dataB[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Mat B(3, 3, CV_32F, dataB);
    cout<<"B = "<<B<<endl;

    Mat B1 = B.clone();
    completeSymm(B1);
    cout<<"B1 = "<<B1<<endl;

    Mat B2 = B.clone();
    completeSymm(B2, true);
    cout<<"B2 = "<<B2<<endl;

    return 0;
}