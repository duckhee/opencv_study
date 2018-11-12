#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataX[] = {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1};
    Mat X(3, 4, CV_32F, dataX);
    cout<<"X = "<<X<<endl;

    Mat covar, mean;
    calcCovarMatrix(X, covar, mean, COVAR_NORMAL + COVAR_COLS + COVAR_SCALE);
    cout<<"mean = "<<mean<<endl;
    cout<<"covar = "<<covar<<endl<<endl;
    Mat Y[4];

    for(int i = 0; i < X.cols; i++)
    {
        Y[i] = X.col(i);
    }
    
    Mat covar2, mean2;
    calcCovarMatrix(Y, X.rows, covar2, mean2, COVAR_NORMAL + COVAR_COLS + COVAR_SCALE);
    cout<<"mean2 = "<<mean2<<endl;
    cout<<"covar2 = "<<covar2<<endl<<endl;

    return 0;
}