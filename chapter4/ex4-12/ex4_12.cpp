#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {10, 20, 30, 40, 50, 60};
    float dataB[] = {10, 20, 30, 100, 200, 300};

    Mat A(2, 3, CV_32F, dataA);
    Mat B(2, 3, CV_32F, dataB);
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;

    Mat dst1;
    compare(A, B, dst1, CMP_EQ);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    compare(A, B, dst2, CMP_GT);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    compare(A, B, dst3, CMP_GE);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    compare(A, 40, dst4, CMP_GE);
    cout<<"dst4 = "<<dst4<<endl;

    Point pt;
    checkRange(A, true, &pt, 10, 35);
    cout<<"pt = "<<pt<<endl;

    Mat dst5;
    inRange(A, 30, 50, dst5);
    cout<<"dst5 = "<<dst5<<endl;

    Mat dst6;
    inRange(A, Scalar(30), Scalar(50), dst6);
    cout<<"dst6 = "<<dst6<<endl;

    return 0;
}