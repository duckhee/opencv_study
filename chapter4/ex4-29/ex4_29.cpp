#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {2, -1, 1, 3, 3, 9, 3, 3, 5};
    Mat A(3, 3, CV_32F, dataA);
    cout<<"A = "<<A<<endl;

    float dataB[] = {-1, 0, 4};
    Mat B(3, 1, CV_32F, dataB);
    cout<<"B = "<<B<<endl;

    Mat X1;
    solve(A, B, X1);
    cout<<"X1 = "<<X1<<endl;

    Mat X2;
    solve(A, B, X2, DECOMP_SVD);
    cout<<"X2 = "<<X2<<endl;

    Mat X3;
    solve(A, B, X3, DECOMP_CHOLESKY);
    cout<<"X3 = "<<X3<<endl;

    Mat X4;
    solve(A, B, X4, DECOMP_EIG);
    cout<<"X4 = "<<X4<<endl;

    Mat X5;
    solve(A, B, X5, DECOMP_QR);
    cout<<"X5 = "<<X5<<endl;

    return 0;
}