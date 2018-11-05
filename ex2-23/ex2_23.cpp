#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(2, 3, CV_32FC1, Scalar(0));
    cout<<"A = "<<A<<endl;

    A.create(2, 3, CV_32FC1);
    cout<<"A = "<<A<<endl;

    A.create(3, 3, CV_32FC1);
    cout<<"A = "<<A<<endl;

    A.create(Size(3, 3), CV_8UC1);
    cout<<"A = "<<A<<endl;

    Mat B;
    int sizes[] = {3, 3};
    B.create(2, sizes, CV_8UC1);
    cout<<"B = "<<B<<endl;
    return 0;
}