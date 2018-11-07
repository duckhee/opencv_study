#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<float> A = (Mat_<float>(3, 3)<< 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cout<<"A = "<<A<<endl;

    Mat B = A.row(0);
    Mat C = A.col(0);
    Mat D0 = A.diag();
    Mat D1 = A.diag(1);
    Mat D2 = A.diag(-1);
    Mat E =A.clone();

    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"C = "<<C<<endl;
    cout<<"D0 = "<<D0<<endl;
    cout<<"D1 = "<<D1<<endl;
    cout<<"D2 = "<<D2<<endl;
    cout<<"E = "<<E<<endl;

    return 0;
}