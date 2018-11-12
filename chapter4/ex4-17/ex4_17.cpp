#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {10, 0, 30, 40, 50, 60};
    Mat A(2, 3, CV_32F, dataA);
    cout<<"A = "<<A<<endl;

    int nCount = countNonZero(A);
    cout<<"nCount = "<<nCount<<endl;

    cout<<"sum(A) = "<<sum(A)<<endl;
    cout<<"mean(A) = "<<mean(A)<<endl;

    Scalar avg, stddev;
    meanStdDev(A, avg, stddev);
    cout<<"avg = "<<avg<<endl;
    cout<<"stddev = "<<stddev<<endl;

    double minVal, maxVal;
    int minIdx[2], maxIdx[2];
    minMaxIdx(A, &minVal, &maxVal, minIdx, maxIdx);
    cout<<"minIdx = ["<<minIdx[0]<<", "<<minIdx[1]<<"]"<<endl;
    cout<<"maxIdx = "<<maxIdx<<endl;

    Point minLoc, maxLoc;
    minMaxLoc(A, &minVal, &maxVal, &minLoc, &maxLoc);
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;
    cout<<"minLoc = "<<minLoc<<endl;
    cout<<"maxLoc = "<<maxLoc<<endl;

    return 0;
}