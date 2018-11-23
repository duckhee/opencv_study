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

    imshow("srcImage", srcImage);

    int border = 3; //7X7
    Size ksize(border * 2 + 1, border * 2 + 1);

    Mat dstImage1;
    boxFilter(srcImage, dstImage1, -1, ksize);
    imshow("dstImage1", dstImage1);

    Mat dstImage2;
    int d = ksize.width;
    double sigmaColor = 10.0;
    double sigmaSpace = 10.0;
    bilateralFilter(srcImage, dstImage2, d, sigmaColor, sigmaSpace);
    imshow("dstImage2", dstImage2);

    Mat dstImage3;
    bilateralFilter(srcImage, dstImage3, -1, sigmaColor, sigmaSpace);
    imshow("dstImage3", dstImage3);

    waitKey();

    return 0;

}