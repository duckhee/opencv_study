#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    Point center(250, 200);
    Size size(200, 100);

    rectangle(dstImage, Point(center.x - size.width, center.y - size.height),
    Point(center.x + size.width, center.y + size.height), Scalar(255, 0, 0));

    line(dstImage, Point(center.x - size.width, center.y),
    Point(center.x + size.width, center.y), Scalar(0, 255, 0));
    line(dstImage, Point(center.x, center.y - size.height), 
    Point(center.x, center.y + size.height), Scalar(0, 255, 0));

    ellipse(dstImage, center, size, 0, 0, 360, Scalar(0, 0, 255), 2);
    ellipse(dstImage, center, size, 90, 45, 360, Scalar(0, 0, 255), 2);

    RotatedRect box(center, size, 90);
    ellipse(dstImage, box, Scalar(255, 0, 0), 2);

    vector<Point> pts;
    ellipse2Poly(center, size, 90, 0, 360, 45, pts);
    polylines(dstImage, pts, true, Scalar(0, 255, 0), 4);

    Point pt1, pt2;
    for(int i = 0; i < pts.size(); i++)
    {
        pt1 = pts[i];
        if(i == pts.size() - 1)
        {
            pt2 = pts[0];
        }
        else
        {
            pt2 = pts[i + 1];
        }
        line(dstImage, pt1, pt2, Scalar(0, 0, 255));
    }

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}