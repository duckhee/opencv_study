#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    if(dstImage.empty())
    {
        return -1;
    }

    Rect imgRect(100, 100, 300, 300);
    rectangle(dstImage, imgRect.tl(), imgRect.br(), Scalar(255, 0, 0), 2);
    
    Point pt1(120, 50), pt2(300, 500);
    line(dstImage, pt1, pt2, Scalar(0, 255, 0), 2);

    clipLine(imgRect, pt1, pt2);
    cout<<"pt1 = "<<pt1<<endl;
    cout<<"pt2 = "<<pt2<<endl;

    circle(dstImage, pt1, 5, Scalar(0, 0, 255), 2);
    circle(dstImage, pt2, 5, Scalar(0, 0, 255), 2);
    line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}