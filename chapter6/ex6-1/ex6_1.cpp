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
        3, 9, 8, 8, 7 ,2, 
        4, 9, 9, 9, 9, 3
    };
    Mat A(6, 6, CV_8U, dataA);
    cout<<"A = "<<A<<endl;

    int border = 2;
    Mat B;
    copyMakeBorder(A, B, border, border, border, border, BORDER_CONSTANT, 0);
    cout<<"B = "<<B<<endl;

    Mat C;
    copyMakeBorder(A, C, border, border, border, border, BORDER_REPLICATE);
    cout<<"C = "<<C<<endl;
    
    Mat D;
    copyMakeBorder(A, D, border, border, border, border, BORDER_REFLECT);

    Mat E;
    copyMakeBorder(A, E, border, border, border, border, BORDER_REFLECT101);
    cout<<"E = "<<E<<endl;

    Mat F;
    copyMakeBorder(A, F, border, border, border, border, BORDER_WRAP);
    cout<<"F = "<<F<<endl;

    waitKey();

    return 0;

}