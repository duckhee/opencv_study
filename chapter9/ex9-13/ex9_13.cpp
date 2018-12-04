#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void onMouse(int event, int x, int y, int flags, void *param);

vector<Point> g_points;

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
    imshow("dstImage", dstImage);
    setMouseCallback("dstImage", onMouse, (void *)&dstImage);

    bool bEscKey = false;
    while(!bEscKey)
    {
        int nKey = waitKey(0);
        switch(nKey)
        {   
            case 27:
                bEscKey = true;
            break;
            case 'r':
                g_points.clear();
                dstImage = Scalar::all(255);
            break;
            case ' ':
                if(g_points.size() < 1)
                {
                    break;
                }
                cout<<"isContourConvex(g_points) = "<<isContourConvex(g_points)<<endl;
                vector<Point> hull;
                convexHull(g_points, hull);
                cout<<"g_points.size() = "<<g_points.size()<<endl;
                cout<<"hull.ssize() = "<<hull.size()<<endl;
                drawContours(dstImage, vector<vector<Point> >(1, hull), 0, Scalar(255, 0, 0), 2);
                cout<<"isContourConvex(hull) = "<<isContourConvex(hull)<<endl;
            break;

        }
        imshow("dstImage", dstImage);

    }
    return 0;
}

void onMouse(int event, int x, int y, int flags, void *param)
{
    Mat *data = (Mat *)param;
    Mat dstImage = *data;
    switch(event)
    {
        case EVENT_MOUSEMOVE:
            if(flags & EVENT_FLAG_LBUTTON)
            {
                circle(dstImage, Point(x, y), 4, Scalar::all(0), -1);
                g_points.push_back(Point(x, y));
            }
        break;
    }
    imshow("dstImage", dstImage);
}