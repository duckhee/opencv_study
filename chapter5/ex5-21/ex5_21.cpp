#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    uchar dataA[16] = {
        0, 0, 0, 0,
        1, 1, 1, 1,
        1, 1, 1, 2,
        1, 2, 1, 3
    };

    Mat A(4, 2, CV_8UC2, dataA);
    cout<<"A = "<<A<<endl;
    int histSize[] = {4, 4};
    float range1[] = {0, 4};
    float range2[] = {0, 4};
    const float* ranges[] = {range1, range2};
    int channels[] = {0, 1};
    int dims = 2;

    Mat hist;
    calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);
    cout<<"hist = "<<hist<<endl;

    Mat backProject;
    calcBackProject(&A, 1, channels, hist, backProject, ranges);
    cout<<"backProject = "<<backProject<<endl;

    return 0;
}