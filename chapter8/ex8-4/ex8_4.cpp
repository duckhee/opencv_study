#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage = imread("./circle.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("no circle image \n");
        return -1;
    }
    //Mat circles;
    vector<Vec3f> circles; //CV_HOUGH_GRANDIENT in OpenCV2.4.13
    HoughCircles(srcImage, circles, HOUGH_GRADIENT, 1, 50);
    cout<<"circles.size() = "<<circles.size()<<endl;
    Mat dstImage(srcImage.size(),  CV_8UC3);
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

    Vec3f params;
    int cx, cy, r;
    //for(int k = 0; k < circles.cols(); k++)
    for(int k = 0; k < circles.size(); k++)
    {
        //params = circles.at<Vec3f>(0, k);
        params = circles[k];
        cx = cvRound(params[0]);
        cy = cvRound(params[1]);
        r = cvRound(params[2]);
        printf("circles[%2d] : (cx, cy) = (%d, %d), r = %d\n", k, cx, cy, r);

        //drawing a line segment
        Point center(cx, cy);
        circle(dstImage, center, r, Scalar(0, 0, 255), 2);
    }
    imshow("dstImage", dstImage);
    waitKey();


    return 0;

}