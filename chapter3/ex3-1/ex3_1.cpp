#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255), 2);

    line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));

    line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0),2, 8, 1);
    //line(dstImage, Point(400/2, 100/2), Point(100/5, 400/2)), Scalar(255, 0, 0);

    rectangle(dstImage, Point(400/2, 100/2), Point(100/2, 400/2), Scalar(255, 0, 0));

    imshow("dstImage", dstImage);
    waitKey();

    return 0;

}