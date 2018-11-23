#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    //Mat srcImage = imread("../rect.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    imshow("srcImage", srcImage);

    Size size(5, 5);
    Mat rectKernel = getStructuringElement(MORPH_RECT, size);
    cout<<"rectKernel = "<<rectKernel<<endl;

    int iterations = 5;
    Point anchor(-1, -1);
    Mat openImage;
    morphologyEx(srcImage, openImage, MORPH_OPEN, rectKernel, anchor, iterations);
    imshow("openImage", openImage);

    Mat closeImage;
    morphologyEx(srcImage, closeImage, MORPH_CLOSE, rectKernel, anchor, iterations);
    imshow("closeImage", closeImage);

    //iterations = 1;
    Mat gradientImage;
    morphologyEx(srcImage, gradientImage, MORPH_GRADIENT, rectKernel, anchor, iterations);
    imshow("gradientImage", gradientImage);

    Mat tophatImage;
    morphologyEx(srcImage, tophatImage, MORPH_TOPHAT, rectKernel, anchor, iterations);
    imshow("tophatImage", tophatImage);

    Mat blackhatImage;
    morphologyEx(srcImage, blackhatImage, MORPH_BLACKHAT, rectKernel, anchor, iterations);
    imshow("blaockhatImage", blackhatImage);

    waitKey();

    return 0;
}