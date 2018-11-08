#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    string text = "OpenCV Programing";
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1.0;

    int thickness = 1;
    int baseLine;
    Point org(100, 100);

    putText(dstImage, text, org, fontFace, fontScale, Scalar(0, 0, 0));
    Size size = getTextSize(text, fontFace, fontScale, thickness, &baseLine);
    rectangle(dstImage, org, Point(org.x + size.width, org.y - size.height), Scalar(0, 0, 255));
    circle(dstImage, org, 3, Scalar(255, 0, 0), 2);

    imshow("dstImage", dstImage);
    waitKey();

    return 0;

}