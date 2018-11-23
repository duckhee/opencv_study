#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

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

    int ksize = 3;
    //double sigma = 0.3 * ((ksize-1) * 0.5 - 1) + 0.8; //when ksize >= 9
    double sigma = 0.0;
    
    Mat kx = getGaussianKernel(ksize, sigma);
    cout<<"kx = "<<kx<<endl;

    Mat ky = getGaussianKernel(ksize, sigma);
    cout<<"ky = "<<ky<<endl;

    Mat kxy = ky * kx.t();
    cout<<"kxy = "<<kxy<<endl;
    cout<<"sum(kxy) = "<<sum(kxy)<<endl;

    Mat dst1;
    sepFilter2D(A, dst1, -1, kx, ky);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    filter2D(A, dst2, -1, kxy);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    GaussianBlur(A, dst3, Size(ksize, ksize), 0.0, 0.0);
    cout<<"dst3 = "<<dst3<<endl;

    waitKey();

    return 0;


}