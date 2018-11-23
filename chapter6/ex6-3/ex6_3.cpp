#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    uchar dataA[] = {
        1, 2, 4, 5, 2, 1, 
        3, 6, 6, 9, 0, 3, 
        1, 8, 3, 7, 2, 5,
        2, 9, 8, 9, 9, 1, 
        3, 9, 8, 8, 7, 2,
        4, 9, 9, 9, 9, 3
    };

    Mat A(6, 6, CV_8U, dataA);
    cout<<"A = "<<A<<endl;
    
    Mat avgKernel = (Mat_<float>(3, 3) << 1./9., 1./9., 1./9., 1./9., 1./9., 1./9., 1./9., 1./9., 1./9.);

    Point anchor(-1, -1); //the same as anchor(1, 1)
    Mat B;
    filter2D(A, B, -1, avgKernel, anchor);
    cout<<"B = "<<B<<endl;

    anchor = Point(1, 1);
    Mat C;
    filter2D(A, C, -1, avgKernel, anchor);
    cout<<"C = "<<C<<endl;

    //convolution
    Point newAnchor = Point(avgKernel.cols - anchor.x - 1, avgKernel.rows - anchor.y -1);
    Mat D;
    Mat flipKernel;
    flip(avgKernel, flipKernel, -1);
    filter2D(A, D, -1, flipKernel, anchor);
    cout<<"D = "<<D<<endl;

    waitKey();

    return 0;

}