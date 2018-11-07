#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Matx33d A(1, -1, -2, 2, -3, -5, -1, 3, 5);
    Matx33d B = A.inv(DECOMP_CHOLESKY);
    Matx33d C = A.inv(DECOMP_LU);

    Matx33d D = A * B;
    Matx33d E = A * C;

    cout<<"A="<<(Mat)A<<endl;
    cout<<"B="<<(Mat)B<<endl;
    cout<<"C="<<(Mat)C<<endl;
    cout<<"D="<<(Mat)D<<endl;
    cout<<"E="<<(Mat)E<<endl;
}