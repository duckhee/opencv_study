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

    Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());
    

    int N = 2;
    int nWidth = srcImage.cols;
    int nHeight = srcImage.rows;
    int x, y;

    Rect rtROI;
    Mat roi;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            x = j * nWidth;
            y = i * nHeight;
            rtROI = Rect(x, y, nWidth, nHeight);
            roi = srcImage(rtROI);
            dstImage(rtROI) = mean(roi);
        }
    }
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}