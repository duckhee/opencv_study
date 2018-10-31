#include "opencv2/opencv.hpp"
//#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Rect rt1(100,100,320,240), rt2(200,200,320,240);
    Point pt1(100, 100);
    Size size(100, 100);

    Rect rt3 = rt1 + pt1;
    Rect rt4 = rt1 + size;

    cout<<"rt1:("<<rt1.x<<", "<<rt1.y<<", "<<rt1.width<<", "<<rt1.height<<")"<<endl;
    cout<<"rt1:"<<rt1<<endl;
    cout<<"rt2:"<<rt2<<endl;
    cout<<"rt3:"<<rt3<<endl;
    cout<<"rt4:"<<rt4<<endl;

    Point ptTopLeft = rt1.tl();
    Point ptBottomRight = rt1.br();
    cout<<"ptTopLeft"<<ptTopLeft<<endl;
    cout<<"ptBottomRight"<<ptBottomRight<<endl;

    Point pt2(200, 200);
    if(rt1.contains(pt2))
    {
        cout<<"pt2 is an inside point in rt1"<<endl;
    }

    Rect rt5 = rt1 & rt2;
    Rect rt6 = rt1 | rt2;
    cout<<"rt5"<<rt5<<endl;
    cout<<"rt6"<<rt6<<endl;

    if(rt1 != rt2)
    {
        cout<<"rt1 and rt2 are not the same rectangle."<<endl;
    }

    Mat img(600, 800, CV_8UC3);
    namedWindow("image", WINDOW_AUTOSIZE);

    rectangle(img, rt1, Scalar(255, 0, 0),2);
    rectangle(img, rt2, Scalar(0, 255, 0),2);
    rectangle(img, rt5, Scalar(0, 0, 255),2);
    imshow("image", img);

    waitKey();

    rectangle(img, rt6, Scalar(0 ,0 ,0),1);
    circle(img, pt2, 5, Scalar(255, 0, 255),2);
    imshow("image", img);
    waitKey();

    return 0;


}