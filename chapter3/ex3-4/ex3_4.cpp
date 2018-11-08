#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255));
    line(dstImage, Point(250, 100), Point(250, 400), Scalar(0, 0, 255));
    line(dstImage, Point(100, 250), Point(400, 250), Scalar(0, 0, 255));
    circle(dstImage, Point(250, 250), 150, Scalar(0, 255, 0));

    circle(dstImage, Point(250, 250), 50, Scalar(0, 255, 0), -1);

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}