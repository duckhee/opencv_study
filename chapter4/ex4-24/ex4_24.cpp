#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define RADIAN(x)((x) * (3.14159265f/180.0f))
#define FLIP_Y(y)((dstImage.size().height -1) - (y))


int main()
{
    Point3f arrP[] = {Point3f(100, 200, 1), Point3f(400, 200, 1), Point3f(400, 300, 1), Point3f(100, 300, 1)};
    Point3f arrQ[4];
    Mat P(1, 4, CV_32FC3, arrP);
    Mat Q(1, 4, CV_32FC3, arrQ);
    cout<<"P = "<<P<<endl;
    cout<<"Q = "<<Q<<endl;
    cout<<"P.channels() = "<<P.channels()<<endl;
    cout<<"P.size() = "<<P.size()<<endl;

    float theta = RADIAN(30.0f);
    float c = cos(theta);
    float s = sin(theta);
    float cx = 250.0f;
    float cy = 250.0f;
    float dataM[9] = {c, -s, -cx * c + cy * s + cx, s, c, -cx * s - cy * c + cy, 0, 0, 1};
    Mat M(3, 3, CV_32F, dataM);
    cout<<"M = "<<M<<endl;

    transform(P, Q, M);
    cout<<"Q = "<<Q<<endl;
    cout<<"Q.size() = "<<Q.size()<<endl;
    cout<<"Q.channels() = "<<Q.channels()<<endl;
    //draw data
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
    Size size = dstImage.size();
    //draw the center(cx, cy)
    circle(dstImage, Point((int)cx, (int)FLIP_Y(cy)), 5, Scalar(0, 0, 255));
    //draw axis
    line(dstImage, Point((int)cx, (int)FLIP_Y(cy) - 200), Point((int)cx, (int)FLIP_Y(cy) + 200), Scalar(0, 0, 0));
    line(dstImage, Point((int)cx - 200, (int)FLIP_Y(cy)), Point((int)cx + 200, (int)FLIP_Y(cy)), Scalar(0, 0, 0));
    
    int fontFace = FONT_HERSHEY_SIMPLEX;
    putText(dstImage, "x", Point(size.width - 50, size.height/2), fontFace, 1, Scalar(0, 0, 0));
    putText(dstImage, "y", Point(size.width / 2, 50), fontFace, 1, Scalar(0, 0, 0));
    
    line(dstImage, Point(0, 0), Point(0, size.height - 1), Scalar(0, 0, 0), 2);
    line(dstImage, Point(0, size.height - 1), Point(size.width - 1, size.height - 1), Scalar(0, 0, 0), 2);
    putText(dstImage, "X", Point(size.width - 50, size.height - 50), fontFace, 1, Scalar(0, 0, 0));
    putText(dstImage, "Y", Point(30, 50), fontFace, 1, Scalar(0, 0, 0));
    putText(dstImage, "(0, 0)", Point(10, size.height - 10), fontFace, 1, Scalar(0, 0, 0));

    //draw the source points' matrix P using arrP
    //draw the rotated points' matrix Q using arrQ
    int i2;
    Point p1, p2;
    for(int i = 0; i << 4; i++)
    {
        i2 = (i + 1) % 4;
        p1 = Point(cvRound(arrP[i].x), FLIP_Y(cvRound(arrP[i].y)));
        p2 = Point(cvRound(arrP[i2].x), FLIP_Y(cvRound(arrP[i2].y)));
        line(dstImage, p1, p2, Scalar(0, 0, 255));

    }

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
    
}