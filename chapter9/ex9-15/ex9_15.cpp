#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../hand.jpg");
    if(srcImage.empty())
    {
        printf("no image \r\n");
        return -1;
    }
    Mat dstImage = srcImage.clone();
    GaussianBlur(srcImage, srcImage, Size(3, 3), 0.0);

    Mat hsvImage;
    cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
    imshow("hsvImage", hsvImage);

    Mat bImage;
    Scalar lowerb(0, 40, 0);
    Scalar upperb(20, 180, 255);
    inRange(hsvImage, lowerb, upperb, bImage);
    //imshow("bImage", bImage);

    vector<vector<Point> > contours;
    findContours(bImage, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    cout<<"contours.size() = "<<contours.size()<<endl;
    if(contours.size() < 1)
    {
        return 0;
    }
    int maxK = 0;
    double maxArea = contourArea(contours[0]);
    for(int k = 1; k < contours.size(); k++)
    {
        double area = contourArea(contours[k]);
        if(area > maxArea)
        {
            maxK = k;
            maxArea = area;
        }
    }
    vector<Point> handContour = contours[maxK];
    //vector<Point> handContour(contours[maxK].size());
    //copy(contours[maxK].begin(), contours[maxK].end(), handContour.begin());

    vector<int> hull;
    convexHull(handContour, hull);
    cout<<"hull.size() = "<<hull.size()<<endl;

    vector<Point> ptsHull;
    for(int k = 0; k < hull.size(); k++)
    {
        int i = hull[k];
        ptsHull.push_back(handContour[i]);
    }
    drawContours(dstImage, vector<vector<Point> >(1, ptsHull), 0, Scalar(255, 0, 0), 2);

    vector<Vec4i> defects;
    convexityDefects(handContour, hull, defects);
    for(int k = 0; k < defects.size(); k++)
    {
        Vec4i v = defects[k];
        Point ptStart = handContour[v[0]];
        Point ptEnd = handContour[v[1]];
        Point ptFar = handContour[v[2]];
        float depth = v[3]/256.0;
        if(depth > 10)
        {
            line(dstImage, ptStart, ptFar, Scalar(0, 255, 0), 2);
            line(dstImage, ptEnd, ptFar, Scalar(0, 255, 0), 2);
            circle(dstImage, ptStart, 6, Scalar(0, 0, 255), 2);
            circle(dstImage, ptEnd, 6, Scalar(0, 0, 255), 2);
            circle(dstImage, ptFar, 6, Scalar(255, 0, 255), 2);
        }
    }
    cout<<"defects.size() = "<<defects.size()<<endl;
    imshow("dstImage", dstImage);
    waitKey(0);
    return 0;
}