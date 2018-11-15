#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    uchar dataA[16] = {
        0, 0, 0, 0,
        1, 1, 3, 5, 
        6, 1, 1, 3,
        4, 3, 1, 7
    };
    Mat A(4, 4, CV_8U, dataA);
    cout<<"A = "<<A<<endl;

    int histSize[] = {4};
    float valueRange[] = {0, 1, 4, 5, 8};
    const float* ranges[] = {valueRange};
    int channels[] = {0};
    int dims = 1;

    Mat hist;
    calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, false);
    cout<<"hist = "<<hist<<endl;

    Mat pdf;
    normalize(hist, pdf, 1, 0, NORM_L1);
    cout<<"pdf = "<<pdf<<endl;

    return 0;
}

