#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    double dataA[] = {1.0, -6.0, 11.0, -6.0};
    double dataB[] = {-6.0, 11.0, -6.0};

    Mat A(1, 4, CV_64F, dataA);
    Mat B(1, 3, CV_64F, dataB);
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;

    Mat X1;
    solveCubic(A, X1);
    cout<<"X1 = "<<X1<<endl;

    Mat X2;
    solveCubic(B, X2);
    cout<<"X2 = "<<X2<<endl;

    Mat A1, X3;
    flip(A, A1, 1);
    cout<<"A1 = "<<A1<<endl;

    solvePoly(A1, X3);
    cout<<"X3.size() = "<<X3.size()<<endl;
    cout<<"X3.channels() = "<<X3.channels()<<endl;
    cout<<"X3 = "<<X3<<endl;

    return 0;
}