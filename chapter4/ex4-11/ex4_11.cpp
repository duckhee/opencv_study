#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    uchar dataA[] = {0x11, 0x12, 0x13, 0x14,0x15, 0x16};
    uchar dataB[] = {0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F};
    uchar dataC[] ={0, 0, 0, 1, 1, 1};

    Mat A(2, 3, CV_8U, dataA);
    Mat B(2, 3, CV_8U, dataB);
    Mat mask(2, 3, CV_8U, dataC);
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"mask = "<<mask<<endl;

    Mat dst1;
    bitwise_and(A, B, dst1);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    bitwise_and(A, B, dst2, mask);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    bitwise_and(A, 0x0F, dst3);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    bitwise_or(A, B, dst4);
    cout<<"dst4 = "<<dst4<<endl;

    Mat dst5;
    bitwise_or(A, B, dst5, mask);
    cout<<"dst5 = "<<dst5<<endl;

    Mat dst6;
    bitwise_or(A, 0x0F, dst6, mask);
    cout<<"dst6 = "<<dst6<<endl;

    Mat dst7;
    bitwise_xor(A, B, dst7);
    cout<<"dst7 = "<<dst7<<endl;

    Mat dst8;
    bitwise_xor(A, B, dst8, mask);
    cout<<"dst8 = "<<dst8<<endl;

    Mat dst9;
    bitwise_xor(A, 0x0F, dst9);
    cout<<"dst9 = "<<dst9<<endl;

    Mat dst10;
    bitwise_not(A, dst10);
    cout<<"dst10 = "<<dst10<<endl;

    return  0;
    
}