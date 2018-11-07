#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<float> A(3,4);
    A = 10;
    cout<<"A = "<<A<<endl;

    Mat B = A;
    cout<<"B = "<<B<<endl;

    Mat_<float> C(3, 4, 10.0f);
    cout<<"C = "<<C<<endl;

    Mat D = A * 0.5 + A/C;
    cout<<"D = "<<D<<endl;

    A = (Mat_<float>(3, 4)<<1, 2, 3, 4, 5, 6, 7, 8, 9);
    cout<<"A.type = "<<A.type()<<".\n A1 = "<<A<<endl;

    Mat A2 = A.row(0);
    cout<<"A2 = "<<A2<<endl;

    //vector<float> V1 = (vector<float>)A2;
    vector<float> V1 = A2;
    V1[0] = 10000.0f;

    cout<<"V1 = "<<(Mat)V1<<endl;

    //Vec<float, 4> V2 = (Vec<float, 4>)A2;
    Vec<float, 4> V2 = A2;
    cout<<"V2 = "<<(Mat)V2<<endl;

    cout<<"A2 = "<<A2<<endl;
    Matx14f m1 = (Matx<float, 1, 4>)A2;
    cout<<"m1 = "<<(Mat)m1<<endl;

    Mat A3 = A;
    //Matx34f m2 = A3;
    Matx34f m2 = (Matx<float, 3, 4>)A;

    cout<<"m2 = "<<(Mat)m2<<endl;
    return 0;
}