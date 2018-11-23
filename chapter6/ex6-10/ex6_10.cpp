#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }

    int ksize = 7;
    Mat dstImage1;
    medianBlur(srcImage, dstImage1, ksize);
    imshow("dstimage1", dstImage1);

    Mat dstImage2;
    blur(srcImage, dstImage2, Size(ksize, ksize));
    imshow("dstImage2", dstImage2);

    Mat dstImage3;
    GaussianBlur(srcImage, dstImage3, Size(ksize, ksize), 0.0);
    imshow("dstImage3", dstImage3);

    ksize = 11;
    Mat dstImage4;
    GaussianBlur(srcImage, dstImage4, Size(ksize, ksize), 0.0);
    imshow("dstImage4", dstImage4);

    Mat kx = getGaussianKernel(ksize, 0.0);
    Mat ky = getGaussianKernel(ksize, 0.0);
    Mat kxy = kx * ky.t();

    Mat dstImage5;
    sepFilter2D(srcImage, dstImage5, -1, kx, ky);
    imshow("dstImage5", dstImage5);

    Mat dstImage6;
    filter2D(srcImage, dstImage6, -1, kxy);
    imshow("dstImage6", dstImage6);

    waitKey();

    return 0;
    
}