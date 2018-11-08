#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("not image.\r\n");
        return -1;
    }

    Rect rtROI(0, 0, 256, 256);
    Mat roi = srcImage(rtROI);
    rectangle(srcImage, rtROI, Scalar::all(0));
    imshow("srcImage", srcImage);

    Mat dstImage = repeat(roi, 2, 2);
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}