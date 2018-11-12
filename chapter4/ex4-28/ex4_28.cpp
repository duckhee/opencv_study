#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {2, -1, 1, 3, 3, 9, 3, 3, 5};
    Mat A(3, 3, CV_32F, dataA);
    cout<<"A = "<<A<<endl;

    Mat invLU;
    double dRet1 = invert(A, invLU);
    cout<<"invLU = "<<invLU<<endl;
    cout<<"dRet = "<<dRet1<<endl;
    cout<<"A*invLU = "<<A*invLU<<endl;

    Mat invSVD;
    double dRet2 = invert(A, invSVD, DECOMP_SVD);
    cout<<"invSVD = "<<invSVD<<endl;
    cout<<"dRet2 = "<<dRet2<<endl;
    cout<<"A * invSVD = "<<A * invSVD<<endl;

    //Accoding to OpenCV document, in Cholesky decopmposition,
    //the matrix must be symmetrical and positively defined.
    //But here A is not a symmetric matrix.
    Mat invCHO;
    double dRet3 = invert(A, invCHO, DECOMP_CHOLESKY);
    cout<<"invCHO = "<<invCHO<<endl;
    cout<<"dRet3 = "<<dRet3<<endl;
    cout<<"A * invCHO = "<<A*invCHO<<endl;

    float dataB[] = {-1, 0, 4};
    Mat B(3, 1, CV_32F, dataB);
    cout<<"B = "<<B<<endl;

    Mat X1 = invLU * B;
    cout<<"X1 = "<<X1<<endl;

    Mat X2 = invSVD * B;
    cout<<"X2 = "<<X2<<endl;

    Mat X3 = invCHO * B;
    cout<<"X3 = "<<X3<<endl;

    return 0;
}