#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataX[] = {0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1};
    Mat X(4, 3, CV_32F, dataX);
    cout<<"X = "<<X<<endl;

    Mat mX;
    reduce(X, mX, 0, REDUCE_AVG);
    cout<<"mX = "<<mX<<endl;

    Mat Cx;
    mulTransposed(X, Cx, true, mX, 1.0/X.rows);
    cout<<"Cx = "<<Cx<<endl;

    return 0;
    
}