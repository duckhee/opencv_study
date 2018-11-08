#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    Point pts1[4] = {Point(100, 100), Point(200, 100), Point(200, 200), Point(100, 200)};
    Point pts2[3] = {Point(300, 200),  Point(400, 100), Point(400, 200)};

    const Point *polygon[2] = {pts1, pts2};
    int npts[2] = {4, 3};

    polylines(dstImage, polygon, npts, 2, true, Scalar(255, 0, 0));
    //polylines(dstImage, polygon, npts, 2, false, Scalar(255, 0, 0));
    //fillConvexPoly(dstImage, polygon[0], npts[0], Scalar(0, 0, 255));
    //fillConvexPoly(dstImage, polygon[1], npts[1], Scalar(255, 0, 0));
    //fillPoly(dstImage, contour, npts Scalar(0, 0, 255));

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}