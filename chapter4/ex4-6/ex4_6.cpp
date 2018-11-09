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

    vector<Mat> images(1, srcImage);
    //images.push_back(srcImage);

    vector<Mat> planes(1, Mat(srcImage.rows, srcImage.cols, srcImage.type()));
    int fromTo[] = {0, 0, 0, 1, 0, 2};
    mixChannels(images, planes, fromTo, 3);

    Mat dstImage = planes[0];
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
    
}