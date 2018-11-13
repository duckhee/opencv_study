#include "opencv2/opencv.hpp"
#include <time.h>

using namespace cv;
using namespace std;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));

    int nPoints = 100;
    Mat randPoints(1, nPoints, CV_32SC2);

    RNG &rng = theRNG();
    rng.state = time(NULL);

    Scalar mean = Scalar(256, 256);
    Scalar stddev = Scalar(50, 50);
    rng.fill(randPoints, RNG::NORMAL, mean, stddev);

    /*
    for(int i = 0; i < randPoints; i++)
    {
        Point pt;
        pt.x = rng.gaussian(stddev.val[0]);
        pt.x += mean.val[0];
        pt.y = rng.gaussian(stddev.val[1]);
        pt.y += mean.val[1];
        randPoints.at<Point>(o, i) = pt;
    }
    */
   //draw points
   for(int x = 0; x < randPoints.cols; x++)
   {
       Point pt = randPoints.at<Point>(0, x);
       circle(dstImage, pt, 3, Scalar(0, 0, 0));
   }
   circle(dstImage, Point(mean.val[0], mean.val[1]), 3, Scalar(0, 0, 255), 3);
   imshow("dstImage", dstImage);
   waitKey();

   return 0;

}