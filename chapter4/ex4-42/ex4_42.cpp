#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define FLIP_Y(y)((dstImage.size().height - 1) - (y))

int main()
{
    double dataX[] = {
        0, 0, 0, 100, 100, 150, -100, -150,
        0, 50, -50, 0, 30, 100, -20, -100
    };

    Mat X(2, 8, CV_64F, dataX);
    cout<<"X = "<<X<<endl;

    Mat cX, mX;
    calcCovarMatrix(X, cX, mX, COVAR_NORMAL + COVAR_COLS);
    cout<<"mX = "<<mX<<endl;
    cout<<"cX = "<<cX<<endl<<endl;

    Mat eValsX;
    Mat eVectsX;
    eigen(cX, eValsX, eVectsX);
    cout<<"eValsX = "<<eValsX<<endl;
    cout<<"eVectsX = "<<eVectsX<<endl<<endl;

    //PCA projection : start
    Mat X1 = X.clone();
    for(int x = 0; x < X1.cols; x++)
    {
        X1.col(x) = X.col(x) - mX;
    }
    Mat A = eVectsX.clone();
    Mat Y = A * X1;
    cout<<"Y = "<<Y<<endl;
    //PCA projection : end

    //PCA backprojection : start
    Mat X2 = A.t() * Y;
    for(int x = 0; x < X2.cols; x++)
    {
        X2.col(x) = X2.col(x) + mX;
    }
    cout<<"X2 = "<<X2<<endl;
    //PCA backprojection : end

    Mat cY, mY;
    calcCovarMatrix(Y, cY, mY, COVAR_NORMAL + COVAR_COLS);
    cout<<"mY = "<<mY<<endl;
    cout<<"cY = "<<cY<<endl<<endl;

    Mat eValsY;
    Mat eVectsY;
    eigen(cY, eValsY, eVectsY);
    cout<<"eValsY = "<<eValsY<<endl;
    cout<<"eVectsY = "<<eVectsY<<endl<<endl;

    //for Mahalanobis dstrance
    Mat invCx;
    invert(cX, invCx);
    Mat invCy;
    invert(cY, invCy);

    //draw points and axis
    Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
    Point ptCenter(dstImage.cols/2, dstImage.rows/2);

    int x, y;
    Mat vec2(2, 1, CV_64F);
    double fDistance1, fDistance2;
    for(y = 0; y < dstImage.rows; y++)
    {
        for(x = 0; x < dstImage.cols; x++)
        {
            vec2.at<double>(0, 0) = x - ptCenter.x;
            vec2.at<double>(1, 0) = y - ptCenter.y;
            fDistance1 = Mahalanobis(mX, vec2, invCx);
            if(0.7 <= fDistance1 && fDistance1 <= 0.8)
            {
                dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(0, 0, 255);
            }
            fDistance2 = Mahalanobis(mY, vec2, invCy);
            if(0.7 <= fDistance2 && fDistance2 <= 0.8)
            {
                dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(255, 0, 0);
            }
        }
    }

    //draw points on the image
    Point pt1, pt2;
    for(x = 0; x < X.cols; x++)
    {
        //draw X
        pt1.x = X.at<double>(0, x) + ptCenter.x;
        pt1.y = X.at<double>(1, x) + ptCenter.y;
        pt1.y = FLIP_Y(pt1.y);
        circle(dstImage, pt1, 3, Scalar(0, 0, 255), 3);

        //draw Y
        pt2.x = Y.at<double>(0, x) + ptCenter.x;
        pt2.y = Y.at<double>(1, x) + ptCenter.y;
        pt2.y = FLIP_Y(pt2.y);
        circle(dstImage, pt2, 3, Scalar(255, 0, 0), 3);
    }

    //draw mX
    pt1.x = cvRound(mX.at<double>(0, 0)) + ptCenter.x;
    pt1.y = cvRound(mX.at<double>(1, 0)) + ptCenter.y;
    pt1.y = FLIP_Y(pt1.y);
    circle(dstImage, pt1, 3, Scalar(255, 0, 255), 3);

    //draw mY
    pt2.x = cvRound(mY.at<double>(0, 0)) + ptCenter.x;
    pt2.y = cvRound(mY.at<double>(1, 0)) + ptCenter.y;
    pt2.y = FLIP_Y(pt2.y);
    circle(dstImage, pt2, 3, Scalar(0, 0, 0), 3);

    //draw X, Y axes
    pt1 = Point(0, ptCenter.y);
    pt2 = Point(dstImage.cols - 1, ptCenter.y);
    line(dstImage, pt1, pt2, Scalar(0, 0, 0), 2);

    pt1 = Point(ptCenter.x, 0);
    pt2 = Point(ptCenter.x, dstImage.rows - 1);
    line(dstImage, pt1, pt2, Scalar(0, 0, 0), 2);

    //draw eigen vectors for X
    double scale = sqrt(eValsX.at<double>(0, 0));
    double x1, y1, x2, y2;
    //draw eVectsX(0)
    x1 = scale * eVectsX.at<double>(0, 0);
    y1 = scale * eVectsX.at<double>(0, 1);
    x2 = -x1;
    y2 = -y1;

    x1 += mX.at<double>(0, 0) + ptCenter.x;
    y1 += mX.at<double>(1, 0) + ptCenter.y;
    x2 += mX.at<double>(0, 0) + ptCenter.x;
    y2 += mX.at<double>(1, 0) + ptCenter.y;

    pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
    pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
    line(dstImage, pt1, pt2, Scalar(0, 0, 255),2);

    //draw eVectsX(1)
    scale = sqrt(eValsX.at<double>(1, 0));
    x1 = scale * eVectsX.at<double>(1, 0);
    y1 = scale * eVectsX.at<double>(1, 1);
    x2 = -x1;
    y2 = -y1;

    x1 += mX.at<double>(0, 0) + ptCenter.x;
    y1 += mX.at<double>(1, 0) + ptCenter.y;
    x2 += mX.at<double>(0, 0) + ptCenter.x;
    y2 += mX.at<double>(1, 0) + ptCenter.y;

    pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
    pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
    line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);
    imshow("dstImage", dstImage);
    waitKey();

    return 0;

}