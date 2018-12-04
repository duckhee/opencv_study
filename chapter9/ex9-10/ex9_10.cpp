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
            case ' ':
                if(g_points.size() < 1)
                {
                    break;
                }
                cout<<"g_pints.size() = "<<g_points.size()<<endl;
                //const Point *pts = (const Point*)Mat(g_points).data;
                const Point *pts = (const Point *)g_points.data();

                int npts = g_points.size(); //Mat(g_points).rows;
                polylines(dstImage, &pts, &npts, 1, closed, Scalar(255, 0, 0), 2);

                //double length = arcLength(Mat(g_points), closed);
                double length = arcLength(g_points, closed);
                cout<<"arcLength = "<<length<<endl;
                
                double area = contourArea(g_points, true);
                cout<<"contouArea = "<<area<<endl;

                Rect rect = boundingRect(g_points);
                rectangle(dstImage, rect, Scalar(0, 0, 255), 2);

                Point2f center;
                float radius;
                minEnclosingCircle(g_points, center, radius);
                circle(dstImage, center, radius, Scalar(0, 255, 0), 2);

                RotatedRect minRect = minAreaRect(g_points);
                Point2f rectPoints[4];
                minRect.points(rectPoints);
                for(int j = 0; j < 4; j++)
                {
                    line(dstImage, rectPoints[j], rectPoints[(j+1)%4], Scalar(255, 0, 255), 2);
                }
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