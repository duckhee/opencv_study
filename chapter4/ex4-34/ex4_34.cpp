#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    double dataX[] = {10, 0, 1, 1, 10, 0, 10, 10, 0, 1, 0, 10, 0, 1, 1};
    Mat X(5, 3, CV_64F, dataX);
    cout<<"x = "<<X<<endl;

    Mat mX;
    reduce(X, mX, 1, REDUCE_AVG);
    cout<<"mX = "<<mX<<endl;

    Mat A(X.rows, X.cols, CV_64F);
    for(int i = 0; i < A.cols; i++)
    {
        A.col(i) = X.col(i) - mX;
    }
    Mat cX = A * A.t();
    cout<<"cX = "<<cX<<endl<<endl;

    Mat eVals;
    Mat eVects;
    eigen(cX, eVals, eVects);
    cout<<"eVals = \n"<<eVals<<endl;
    cout<<"eVects = \n"<<eVects<<endl;

    Mat cX2 = A.t() * A;
    cout<<"cX2 = "<<cX2<<endl;

    Mat eVals2;
    Mat eVects2;
    eigen(cX2, eVals2, eVects2);
    cout<<"eVals2 = "<<eVals2<<endl;
    cout<<"eVects2 = "<<eVects2<<endl;

    //Calculate some of eVects from eVects2
    Mat A2(X.rows, X.cols, CV_64F);
    for(int i = 0; i < A.cols; i++)
    {
        A2.col(i) = X.col(i) - mX;
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