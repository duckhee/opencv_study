#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Point2f ptCenter(200.0f, 200.0f);
    Size size(100, 200);

    RotatedRect rt1(ptCenter, size, 135.0f);

    Point2f points[4];

    rt1.points(points);

    Rect rt2 = rt1.boundingRect();

    cout<<"rt1: ptCencter("<<rt1.center.x<<", "<<rt1.center.y<<"), "
    <<"size = ("<<rt1.size.width<<", "<< rt1.size.height<<"), "
    <<"(angle = "<<rt1.angle<<")"<<endl;

    cout<<"rt2:("<<rt2.x<<", "<<rt2.y<<", "
    << rt2.width<<", "<<rt2.height<<")"<<endl;

    for(int i = 0; i < 4; i++)
    {
        cout<<"points["<<i<<"]="<<points[i]<<endl;
    }
    Mat image(400, 400, CV_8UC3, Scalar(255, 255, 255));

    for(int i = 0; i < 4; i++)
    {
        line(image, points[i], points[(i+1)%4], Scalar(0, 0, 255));
    }

    rectangle(image, rt2, Scalar(255, 0, 0));
    circle(image, ptCenter, 5, Scalar(255, 0, 255), 2);
    imshow("image", image);

    waitKey();

    return 0;

}