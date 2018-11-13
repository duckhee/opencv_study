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
    Mat_<uchar>image(srcImage);
    Mat_<uchar>dstImage(srcImage.size());

    for(int y = 0; y < srcImage.rows; y++)
    {
        for(int x = 0; x < srcImage.cols; x++)
        {
            uchar r = image(y, x);
            dstImage(y, x) = 255-r;
        }
    }
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}