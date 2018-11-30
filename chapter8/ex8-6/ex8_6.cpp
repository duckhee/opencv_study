#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat rgbImage = imread("hand.jpg");
    //Mat rgbImage = imread("flower.jpg");

    imshow("rgbImage", rgbImage);

    Mat hsvImage;
    cvtColor(rgbImage, hsvImage, COLOR_BGR2HSV);
    imshow("hsvImage", hsvImage);

    //hand.jpg
    Scalar lowerb(0, 40, 0);
    Scalar upperb(20, 180, 255);

    //flower.jpg
    //Scalar lowerb(150, 100, 100);
    //Scalar upperb(180, 255,255);

    Mat dstImage;
    inRange(hsvImage, lowerb, upperb, dstImage);
    imshow("dstImage1", dstImage);

    //check HSV range in object(hand or flower)
    vector<Mat> planes;
    split(hsvImage, planes);
    //imshow("planes[0], planes[0]");
    //imshow("planes[1], planes[1]");
    //imshow("planes[2], planes[2]");

    double minH, maxH;
    minMaxLoc(planes[0], &minH, &maxH, NULL, NULL, dstImage);
    cout<<"minH = "<<minH<<endl;
    cout<<"maxH = "<<maxH<<endl;

    double minS, maxS;
    minMaxLoc(planes[1], &minS, &maxS, NULL, NULL, dstImage);
    cout<<"minS = "<<minS<<endl;
    cout<<"maxS = "<<maxS<<endl;

    double minV, maxV;
    minMaxLoc(planes[2], &minV, &maxV, NULL, NULL, dstImage);
    cout<<"minV = "<<minV<<endl;
    cout<<"maxV = "<<maxV<<endl;

    waitKey();

    return 0;

}