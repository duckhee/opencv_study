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
        }
        imshow("dstImage", dstImage);
    }
    return 0;
}

void onMouse(int event, int x, int y, int flags, void *param)
{
    Mat *data = (Mat *)param;
    Mat dstImage = *data;

    int npts;
    const Point *pts;
    double dist;
    switch(event)
    {
        case EVENT_MOUSEMOVE:
            if(flags & EVENT_FLAG_LBUTTON)
            {
                circle(dstImage, Point(x, y), 4, Scalar::all(0), -1);
                g_points.push_back(Point(x, y));
            }
        break;
        case EVENT_FLAG_RBUTTON:
            dstImage = Scalar::all(255);
            circle(dstImage, Point(x, y), 4, Scalar::all(0), -1);

            npts = g_points.size();
            pts = (Point *)g_points.data();
            polylines(dstImage, &pts, &npts, 1, true, Scalar(255, 0, 0), 2);
            dist = pointPolygonTest(g_points, Point(x, y), true);
            cout<<"dist = "<<dist<<endl;
            if(dist > 0)
            {
                circle(dstImage, Point(x, y), 5, Scalar(0, 255, 0), 4);
            }
            else if(dist < 0)
            {
                circle(dstImage, Point(x, y), 5, Scalar(0, 0, 255), 4);
            }
            else
            {
                circle(dstImage, Point(x, y), 5, Scalar(255, 255, 0), 4);
            }
        break;
    }
    imshow("dstImage", dstImage);
}