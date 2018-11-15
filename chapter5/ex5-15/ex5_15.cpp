#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
        return -1;

    Mat dstImage;
    equalizeHist(srcImage, dstImage);

    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(100);
    imwrite("ex5_15.jpg", dstImage, params);

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}