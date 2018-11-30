#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("./Heart10.jpg", IMREAD_GRAYSCALE);
    //Mat srcImage = imread("./testImage.bmp", IMREAD_GRAYSCALE);

    GaussianBlur(srcImage, srcImage, Size(7, 7), 0.0, 0.0);
    imshow("srcImage", srcImage);

    Mat dstImage1;
    double th1 = threshold(srcImage, dstImage1, 128, 255, THRESH_BINARY | THRESH_OTSU);
    cout<<"th1 = "<<th1<<endl;

    int blockSize = 71; //7, 31, 71
    int C = 5;
    Mat dstImage2;
    adaptiveThreshold(srcImage, dstImage2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, blockSize, C);

    Mat dstImage3;
    adaptiveThreshold(srcImage, dstImage3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, blockSize, C);

    imshow("THRESH_OTSU", dstImage1);
    imshow("MEAN_C", dstImage2);
    imshow("GAUSSIAN_C", dstImage3);
    waitKey();

    return 0;
}