#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {-2, 2, -3, -1, 1, 3, 2, 0, -1};
    Mat A(3, 3, CV_32F, dataA);
    Mat B, C, D, E;
    B = abs(A);
    convertScaleAbs(A, C);

    convertScaleAbs(A, D, 2.0, 1.0);
    E = abs(A * 2.0 + 1);

    Mat dst;
    //absdiff(D, E, dst);
    absdiff(C, D, dst);

    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;
    cout<<"D = "<<D<<endl;
    cout<<"E = "<<E<<endl;
    cout<<"dst = "<<dst<<endl;

    return 0;
}