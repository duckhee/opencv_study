#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void myThreshold(InputArray _src, OutputArray _dst, uchar thresh);

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);

    if(srcImage.empty())
    {
        return -1;
    }

    Mat dstImage;
    myThreshold(srcImage, dstImage, 128);
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}

void myThreshold(InputArray _src, OutputArray _dst, uchar thresh)
{
    Mat src = _src.getMat();
    _dst.create(src.size(), src.type());
    Mat dst = _dst.getMat();

    for(int i = 0; i < src.rows; i++)
    {
        for(int j = 0; j < src.cols; j++)
        {
            if(src.at<uchar>(i, j) < thresh)
            {
                dst.at<uchar>(i, j) = 0;
            }
            else
            {
                dst.at<uchar>(i, j) = 255;
            }
        }
    }
}