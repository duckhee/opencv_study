#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 521, CV_8UC3, Scalar(255, 255, 255));

    vector<vector<Point> > contour(2, vector<Point>());
    contour[0].push_back(Point(100, 100));
    contour[0].push_back(Point(200, 200));
    contour[0].push_back(Point(200, 200));
    contour[0].push_back(Point(100, 200));
    contour[1].push_back(Point(300, 200));
    contour[1].push_back(Point(400, 100));
    contour[1].push_back(Point(400, 200));

    const cv::Point *pts1 = (const cv::Point*)Mat(contour[0]).data;
    const cv::Point *pts2 = (const cv::Point*)Mat(contour[1]).data;

    const Point *polygon[2] = {pts1, pts2};
    int npts[2] = {contour[0].size(), contour[1].size()};

    polylines(dstImage, polygon, npts, 2, true, Scalar(255, 0, 0));
    //polylines(dstImage, polygon, npts, 2, 0, Scalar(255, 0, 0));
    //fillConvexPoly(dstImage, polygon[0], npts[0], Scalar(0, 0, 255));
    //fillConvexPoly(dstImage, polygon[1], npts[1], Scalar(255, 0, 0));
    //fillPoly(dsImage, polygon, npts, 2, Scalar(0, 0, 255));

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}