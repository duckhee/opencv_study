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

    Scalar a = Scalar::all(0);
    Scalar b = Scalar(dstImage.cols, dstImage.rows);
    rng.fill(randPoints, RNG::UNIFORM, a, b);
    /*
        for(int i = 0; i < randPoints.cols; i++)
        {
            Point pt;
            pt.x = rng.uniform(a.val[0], b.val[0]);
            pt.y = rng.uniform(a.val[0], b.val[1]);
        }
     */
    //draw points
    for(int x = 0; x < randPoints.cols; x++)
    {
        Point pt = randPoints.at<Point>(0,x);
        circle(dstImage, pt, 3, Scalar(0, 0, 0));
    }
    imshow("dstImage", dstImage);
    waitKey();
    return 0;
}