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
    Mat mX;
    reduce(X, mX, 1, REDUCE_AVG);
    cout<<"mX = "<<mX<<endl;

    PCA pca(X, mX, 1);
    Mat Y;
    pca.project(X, Y);
    cout<<"Y = "<<Y<<endl;
    Mat mY;
    reduce(Y, mY, 1, REDUCE_AVG);
    cout<<"mY = "<<mY<<endl;

    Mat X2;
    pca.backProject(Y, X2);
    cout<<"X2 = "<<X2<<endl;

    cout<<"pca.mean = "<<pca.mean<<endl;
    cout<<"pca.eigenvalues = "<<pca.eigenvalues<<endl;
    cout<<"pca.eigenvectors = "<<pca.eigenvectors<<endl;

    //draw point and axis
    Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
    Point ptCenter(dstImage.cols/2, dstImage.rows/2);

    //draw points on the image
    Point pt1, pt2;
    for(int x = 0; x < X.cols; x++)
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
    pt1.x =cvRound(mX.at<double>(0, 0)) + ptCenter.x;
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
    line(dstImage, pt1, pt2, Scalar(0, 0, 0));
    
    //draw pca.eigenvectors for X
    double scale = sqrt( pca.eigenvalues.at<double>(0, 0) * X.cols );
    double x1, y1, x2, y2;
    //draw pca.eigenvectors(0)
    x1 = scale * pca.eigenvectors.at<double>(0, 0);
    y1 = scale * pca.eigenvectors.at<double>(0, 1);
    x2 = -x1;
    y2 = -y1;

    x1 += mX.at<double>(0, 0) + ptCenter.x;
    y1 += mX.at<double>(1, 0) + ptCenter.y;
    x2 += mX.at<double>(0, 0) + ptCenter.x;
    y2 += mX.at<double>(1, 0) + ptCenter.y;

    pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
    pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
    line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);

    //draw pca.eigenvectors(1)
    scale = sqrt(pca.eigenvalues.at<double>(1, 0) * X.cols);
    x1 = scale * pca.eigenvectors.at<double>(1, 0);
    y1 = scale * pca.eigenvectors.at<double>(1, 1);
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