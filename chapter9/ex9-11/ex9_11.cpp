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

    int npts;
    const Point *pts;
    Point ptStart, ptEnd;
    float s = 1000;
    int distType = DIST_L2; //CV_DIST_L2
    Vec4f lineFit;

    vector<Point> approxCurve;
    double epsilon = 50;
    bool closed = false;
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
            case '1':
                if(g_points.size() < 1)
                {
                    break;
                }
                dstImage = Scalar::all(255);
                npts = g_points.size();
                pts = (Point *)g_points.data();
                polylines(dstImage, &pts, &npts, 1, closed, Scalar(0, 255,0), 2);

                fitLine(g_points, lineFit, distType, 0, 0.01, 0.01);
                ptStart.x = cvRound(s*lineFit[0] + lineFit[2]);
                ptStart.y = cvRound(s*lineFit[1] + lineFit[3]);
                ptEnd.x = cvRound(-s*lineFit[0] + lineFit[2]);
                ptEnd.y = cvRound(-s*lineFit[1] + lineFit[3]);
                line(dstImage, ptStart, ptEnd, Scalar(255, 0, 0), 2);
            break;
            case '2':
                if(g_points.size() < 1)
                {
                    break;
                }
                dstImage = Scalar::all(255);
                cout<<"g_points.size() = "<<g_points.size()<<endl;
                npts = g_points.size();
                pts = (Point *)g_points.data();
                polylines(dstImage, &pts, &npts, 1, closed, Scalar(0, 255, 0), 2);
            break;
            case '3':
                if(g_points.size() < 1)
                {
                    break;
                }
                dstImage = Scalar::all(255);
                cout<<"g_points.size() = "<<g_points.size()<<endl;
                npts = g_points.size();
                pts = (Point *)g_points.data();
                polylines(dstImage, &pts, &npts, 1, closed, Scalar(0, 255, 0), 2);

                RotatedRect rect;
                rect = fitEllipse(g_points);
                ellipse(dstImage, rect, Scalar(0, 0, 255), 2);
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