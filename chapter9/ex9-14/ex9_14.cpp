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

    vector<int> hull;
    vector<Point> ptsHull;
    vector<Vec4i> defects;
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
                cout<<"g_points.size() = "<<g_points.size()<<endl;

                convexHull(g_points, hull);
                cout<<"hull.size() = "<<hull.size()<<endl;
                
                ptsHull.clear();
                for(int k = 0; k < hull.size(); k++)
                {
                    int i = hull[k];
                    ptsHull.push_back(g_points[i]);
                }
                drawContours(dstImage, vector<vector<Point> >(1, ptsHull), 0, Scalar(255, 0, 0), 2);
                convexityDefects(g_points, hull, defects);
                for(int k = 0; k < defects.size(); k++)
                {
                    Vec4i v = defects[k];
                    Point ptStart = g_points[v[0]];
                    Point ptEnd = g_points[v[1]];
                    Point ptFar = g_points[v[2]];
                    float depth = v[3] / 256.0;
                    if(depth > 10)
                    {
                        line(dstImage, ptStart, ptFar, Scalar(0, 255, 0), 2);
                        line(dstImage, ptEnd, ptFar, Scalar(0, 255, 0), 2);
                        circle(dstImage, ptStart, 6, Scalar(0, 0, 255), 2);
                        circle(dstImage, ptEnd, 6, Scalar(0, 0, 255), 2);
                        circle(dstImage, ptFar, 6, Scalar(255, 0, 255), 2);

                    }
                }
                cout<<"defects.size() = "<<defects.size()<<endl;
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
                circle(dstImage, Point(x, y), 2, Scalar::all(0), -1);
                g_points.push_back(Point(x, y));
            }
        break;
    }
    imshow("dstImage", dstImage);
}