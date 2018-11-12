#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    double dataX[] = {10, 0, 1, 1, 10, 0, 10, 10, 0, 1, 0, 10, 0, 1, 1};
    Mat X(5, 3, CV_64F, dataX);
    cout<<"X = "<<X<<endl;

    Mat cX, mX;
    calcCovarMatrix(X, cX, mX, COVAR_NORMAL + COVAR_COLS);
    cout<<"mX = "<<mX<<endl;
    cout<<"cX = "<<cX<<endl<<endl;

    Mat eVals;
    Mat eVects;
    eigen(cX, eVals, eVects);
    cout<<"eVals = \n"<<eVals<<endl;
    cout<<"eVect = \n"<<eVects<<endl;



    Mat cX2, mX2;
    calcCovarMatrix(X, cX2, mX2, COVAR_SCRAMBLED + COVAR_COLS);
    cout<<"mX2 = "<<mX2<<endl;
    cout<<"cX2 = "<<cX2<<endl;

    Mat eVals2;
    Mat eVects2;
    eigen(cX, eVals2, eVects2);
    cout<<"eVals2 = \n"<<eVals2<<endl;
    cout<<"eVects2 = \n"<<eVects2<<endl<<endl;

    //Calculate some of eVects from eVects2
    Mat A(X.rows, X.cols, CV_64F);
    cout<<"A = "<<A<<endl;
    cout<<"mX = "<<mX<<endl;
    for(int i = 0; i < A.cols; i++)
    {
        //cout<<"A.col"<<A.col(i)<<", "<<"X.col"<<X.col(i)<<", mx"<<mX<<endl;
        A.col(i) = X.col(i) - mX;
    }
    
    Mat eVects3 = A * eVects2.t();

    Mat a;
    for(int i = 0; i < eVects3.cols; i++)
    {
        a = eVects3.col(i);
        normalize(a, a);
    }
    cout<<"eVects3.t() = "<<eVects3.t()<<endl;

    return 0;
}