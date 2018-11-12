#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define FLIP_Y(y) ((dstImage.size().height - 1) - (y))


int main()
{
    double dataX[] = {0, 0, 0, 100, 100, 150, -100, -150, 0, 50, -50, 0, 30, 100, -20, -100};
    Mat X(2, 8, CV_64F, dataX);
    cout<<"X = "<<X<<endl;

    Mat cX, mX;
    calcCovarMatrix(X, cX, mX, COVAR_NORMAL + COVAR_COLS);
    cout<<"mX = "<<mX<<endl;
    cout<<"cX = "<<cX<<endl;

    Mat invCx;
    invert(cX, invCx);
    cout<<"invCx = "<<invCx<<endl;

    Mat vec1 = (Mat_<double>(2, 1) << 0, 50);
    Mat vec2 = (Mat_<double>(2, 1) << 0, 100);

    double fDistance = Mahalanobis(vec1, vec2, invCx);
    cout<<"fDistance  = "<<fDistance<<endl;

    Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
    Point ptCenter(dstImage.cols/2, dstImage.rows/2);

    //cout<<"mX.size() = "<<mX.size()<<endl;
    //cout<<"vec2.size() = "<<vec2.size()<<endl;
    //cout<<"invCx.size() = "<<invCx.size()<<endl;

    int x, y;
    for(y = 0; y < dstImage.rows; y++)
    {
        for(x = 0; x < dstImage.cols; x++)
        {
            vec2.at<double>(0, 0) = x -ptCenter.x;
            vec2.at<double>(1, 0) = y - ptCenter.y;
            fDistance = Mahalanobis(mX, vec2, invCx);
            if(fDistance < 0.1)
            {
                dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(50, 50, 50);
            }
            else if(fDistance < 0.3)
            {
                dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(100, 100, 100);
            }
            else if(fDistance < 0.8)
            {
                dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(200, 200, 200);
            }
            else
            {
                dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(255, 255, 255);
            }
        }
    }

    //draw point on the image
    Point pt;
    for(x = 0; x < X.cols; x++)
    {
        pt.x = X.at<double>(0, x) + ptCenter.x;
        pt.y = X.at<double>(1, x) + ptCenter.y;
        pt.y = FLIP_Y(pt.y);
        circle(dstImage, pt, 3, Scalar(0, 0, 255), 3);
    }

    //draw X, Y, axes
    Point pt1, pt2;
    pt1 = Point(0, ptCenter.y);
    pt2 = Point(dstImage.cols - 1, ptCenter.y);
    line(dstImage, pt1, pt2, Scalar(0, 0, 0));

    //draw eigen vectors
    Mat eVals;
    Mat eVects;

    eigen(cX, eVals, eVects);
    cout<<"eVals = "<<eVals<<endl;
    cout<<"eVects = "<<eVects<<endl;

    double scale = sqrt(eVals.at<double>(0, 0));
    double x1, y1, x2, y2;
    //draw eVects(0)
    x1 = scale * eVects.at<double>(0, 0);
    y1 = scale * eVects.at<double>(0, 1);
    x2 = -x2;
    y2 = -y1;

    x1 += mX.at<double>(0, 0) + ptCenter.x;
    y1 += mX.at<double>(1, 0) + ptCenter.y;
    x2 += mX.at<double>(0, 0) + ptCenter.x;
    y2 += mX.at<double>(1, 0) + ptCenter.y;

    pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
    pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
    line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);

    //draw eVects(1)
    scale = sqrt(eVals.at<double>(1, 0));
    x1 = scale * eVects.at<double>(1, 0);
    y1 = scale * eVects.at<double>(1, 1);
    x2 = -x1;
    y2 = -y1;

    x1 += mX.at<double>(0, 0) + ptCenter.x;
    y1 += mX.at<double>(1, 0) + ptCenter.y;
    x2 += mX.at<double>(0, 0) + ptCenter.x;
    y2 += mX.at<double>(1, 0) + ptCenter.y;

    pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
    pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
    line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);
    imshow("dstImage", dstImage);
    waitKey();

    return  0;

}