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

    Mat dstImage1;
    adaptiveThreshold(srcImage, dstImage1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 5);

    Mat dstImage2;
    adaptiveThreshold(srcImage, dstImage2, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 5);

    imshow("dstImage1", dstImage1);
    imshow("dstImage2", dstImage2);
    waitKey();

    return 0;
}