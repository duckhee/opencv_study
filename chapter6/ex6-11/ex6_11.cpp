#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    uchar dataA[] = {
        1, 1, 1, 1, 1, 1,
        1, 1, 9, 9, 1, 1,
        1, 1, 9, 9, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
    };
    Mat A(6, 6, CV_8U, dataA);
    cout<<"A = "<<A<<endl;

    int dx = 1, dy = 0;
    int ksize = 3;
    Mat kx, ky;
    getDerivKernels(kx, ky, dx, dy, ksize);
    cout<<"kx = "<<kx<<endl;
    cout<<"ky = "<<ky<<endl;

    Mat kxy = ky * kx.t();
    cout<<"kxy = "<<kxy<<endl;

    int ddepth = CV_16S; //the dst?s will be truncated if ddepth = -1
    Mat dst1;
    sepFilter2D(A, dst1, ddepth, kx, ky);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    filter2D(A, dst2, ddepth, kxy);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    Sobel(A, dst3, ddepth, dx, dy, ksize);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    Sobel(A, dst4, ddepth, dx, dy, -1); //CV_SCHARR
    cout<<"dst4 = "<<dst4<<endl;

    Mat dst5;
    Scharr(A, dst5, ddepth, dx, dy);
    cout<<"dst5 = "<<dst5<<endl;

    waitKey();

    return 0;

}