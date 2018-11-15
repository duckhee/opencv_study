#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    uchar dataA[] = {
        0, 0, 0, 0,
        1, 1, 3, 5,
        6, 1, 1, 3, 
        4, 3, 1, 7
    };

    Mat A(4, 4, CV_8U, dataA);
    cout<<"A = "<<A<<endl;

    Mat dst;
    equalizeHist(A, dst);
    cout<<"dst = "<<dst<<endl;

    CvMat pSrcMat = A;
    CvMat *pDstMat = cvCreateMat(4, 4, CV_8U);
    cvEqualizeHist(&pSrcMat, pDstMat);
    Mat dst2 = cvarrToMat(pDstMat);
    cout<<"dst2 = "<<dst2<<endl;

    return 0;
}