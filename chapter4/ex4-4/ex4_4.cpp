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
    vector<Mat> planes;
    split(srcImage, planes);

    //imshow("srcImage", srcImage);
    imshow("planes[0]", planes[0]);
    imshow("planes[1]", planes[1]);
    imshow("planes[2]", planes[2]);

    //planes[0] = 0;
    //Mat dstImage(srcImage.rows, srcImage.cols, srcImage.type();
    Mat dstImage;
    merge(planes, dstImage);
    imshow("dstImage", dstImage);

    waitKey();
    return 0;
}