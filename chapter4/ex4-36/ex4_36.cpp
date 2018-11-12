#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
    int nPoints = 100;
    Mat randPoints(1, nPoints, CV_32SC2);
    theRNG().state = time(NULL);
    randu(randPoints, Scalar::all(0), Scalar(dstImage.cols, dstImage.rows));
    //cout<<randPoints<<endl;
    for(int x = 0; x < randPoints.cols; x++)
    {
        Point pt = randPoints.at<Point>(0, x);
        circle(dstImage, pt, 3, Scalar(0, 0, 0));
    }
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}