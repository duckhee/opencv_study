#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(10, 10, CV_32F);
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A.at<float>(i, j) = (float)(i * A.cols + j);
        }
    }

    cout<<"A = "<<A.size()<<"="<<A<<endl;

    Mat B = A(Range(5, 8), Range(3, 6));
    cout<<"B = "<<B.size()<<"="<<B<<endl;

    Size wholeSize;
    Point ofs;
    B.locateROI(wholeSize, ofs);
    cout<<"wholeSize = "<<wholeSize<<"ofs = "<<ofs<<endl;

    Mat C = B.adjustROI(1, 1, 1, 1);
    cout<<"B = "<<B.size()<<" = "<<B<<endl;
    cout<<"C = "<<C.size()<<" = "<<C<<endl;

    return 0;
}