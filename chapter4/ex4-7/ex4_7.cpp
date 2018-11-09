#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("no image.\r\n");
        return -1;
    }
    IplImage* arrImage = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 3);
    
    //insertImageCOI exception error -214 Assertion failed
    insertImageCOI(srcImage, arrImage, 0);
    insertImageCOI(srcImage, arrImage, 1);
    insertImageCOI(srcImage, arrImage, 2);

    Mat dstImage = cvarrToMat(arrImage);
    imshow("dstImage", dstImage);

    Mat imR, imG, imB;
    extractImageCOI(arrImage, imB, 0);
    extractImageCOI(arrImage, imG, 1);
    extractImageCOI(arrImage, imR, 2);

    imshow("imB", imB);
    imshow("imG", imG);
    imshow("imR", imR);
    waitKey();

    return 0;

}