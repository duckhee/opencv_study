#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg");

    if(srcImage.empty())
    {
        printf("no image.\r\n");
        return -1;
    }
    Mat imR(srcImage.rows, srcImage.cols, CV_8UC1);
    Mat imG(srcImage.rows, srcImage.cols, CV_8UC1);
    Mat imB(srcImage.rows, srcImage.cols, CV_8UC1);

    Mat outImage[] = {imB, imG, imR};
    int fromTo[] = {0, 0, 1, 1, 2, 2};
    //splits(srcImage, outImage);
    mixChannels(&srcImage, 1, outImage, 3, fromTo, 3);

    //Mat dstImage;
    //merge(outImage, 3, dstImage);
    Mat dstImage(srcImage.rows, srcImage.cols, srcImage.type());
    mixChannels(outImage, 3, &dstImage, 1, fromTo, 3);
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}