#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Point3f pt1(1.0f, 0.0f, 0.0f), pt2(0.0f, 1.0f, 0.0f);

    Point3i pt3 = (pt1 + pt2) * 10.0f;
    Point3f pt4 = (pt1 - pt2) * 100.0f;

    cout<<"pt1:"<<pt1<<endl;
    cout<<"pt2:"<<pt2<<endl;
    cout<<"pt3:"<<pt3<<endl;
    cout<<"pt1:"<<pt4<<endl;

    if(pt1 != pt2)
    {
        cout<<"pt1 is not equal to pt2"<<endl;
    }
    else
    {
        cout<<"pt1 is equal to pt2"<<endl;
    }

    float fValue = pt1.dot(pt2);
    cout<<"fValue = "<<fValue<<endl;

    double normValue = norm(pt1);
    cout<<"normValue = "<<normValue<<endl;

    Point3f pt5 = pt1.cross(pt2);
    Point3f pt6 = pt2.cross(pt1);

    cout<<"pt5:"<<pt5<<endl;
    cout<<"pt6:"<<pt6<<endl;

    return 0;
}