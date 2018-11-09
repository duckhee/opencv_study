#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {1, 2, 3, 4, 5, 6};
    float dataB[] = {10, 10, 10, 10, 10, 10};
    uchar dataC[] = {0, 0, 0, 1, 1, 1};

    Mat A(2, 3, CV_32F, dataA);
    Mat B(2, 3, CV_32F, dataB);
    Mat mask(2, 3, CV_8U, dataC);
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"mask = "<<mask<<endl;

    Mat dst1;
    add(A, B, dst1);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    add(A, B, dst2, mask);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    add(A, 100, dst3);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    add(A, Scalar(200), dst4);
    cout<<"dst4 = "<<dst4<<endl;

    Mat dst5;
    scaleAdd(A, 2.0, B, dst5);
    cout<<"dst5 = "<<dst5<<endl;

    Mat dst6;
    addWeighted(A, 1.0, B, 2.0, 10.0, dst6);
    cout<<"dst6 = "<<dst6<<endl;

    Mat dst7;
    subtract(A, B, dst7);
    cout<<"dst7 = "<<dst7<<endl;

    Mat dst8;
    multiply(A, B, dst8);
    cout<<"dst8 = "<<dst8<<endl;

    Mat dst9;
    divide(A, B, dst9);
    cout<<"dst9 = "<<dst9<<endl;

    Mat dst10;
    divide(A, B, dst10);
    cout<<"dst10 = "<<dst10<<endl;

    return 0;
}