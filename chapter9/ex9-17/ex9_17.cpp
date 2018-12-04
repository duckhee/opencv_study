#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

vector<vector<Point> > myFindContours(Mat &srcImage);
void onMouse(int event, int x, int y, int flags, void *param);
vector<Point> g_points;

int main()
{
    Mat refImage = imread("../refShapes.jpg", IMREAD_GRAYSCALE);
    if(refImage.empty())
    {
        printf("refImage not image \r\n");
        return -1;
    }
    Scalar colorTable[] = {
        Scalar(0, 0, 255),
        Scalar(0, 255, 0),
        Scalar(255, 0, 0)
    };

    Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
    imshow("dstImage", dstImage);
    setMouseCallback("dstImage", onMouse, (void *)&dstImage);

    vector<vector<Point> > refContours = myFindContours(refImage);
    if(refContours.size() < 1)
    {
        return 0;
    }
    Mat refRGB;
    cvtColor(refImage, refRGB, COLOR_GRAY2BGR);
    for(int k = 0; k < refContours.size(); k++)
    {
        drawContours(refRGB, refContours, k, colorTable[k], 2);
    }
    imshow("refRGB", refRGB);

    int npts;
    const Point *pts;
    vector<Point> approxCurve;

    int method = 3; //CV_CONTOURS_MATCH_I3 in "type.h"
    int minK;
    double minD;
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
                //cout<<"g_points.size() = "<<g_points.size() << endl;

                approxCurve = g_points;
                //approxPolyDP(g_points, approxCurve, 10, true);

                //matches
                minD = matchShapes(refContours[0], approxCurve, method, 0);
                minK = 0;
                for(int k = 1; k < refContours.size(); k++)
                {
                    double d = matchShapes(refContours[k], approxCurve, method, 0);
                    if(d < minD)
                    {
                        minD = d;
                        minK = k;
                    }
                }
                pts = (const Point *)approxCurve.data();
                npts = approxCurve.size();
                polylines(dstImage, &pts, &npts, 1, true, colorTable[minK], 4);
                //cout<<"minK = "<<minK<<endl;
                break;
        }
        imshow("dstImage", dstImage);
    }
    waitKey(0);
    return 0;
}

vector<vector<Point> > myFindContours(Mat &srcImage)
{
    GaussianBlur(srcImage, srcImage, Size(3, 3), 0.0);
    Mat bImage;
    threshold(srcImage, bImage, 128, 255, THRESH_BINARY_INV + THRESH_OTSU);
    erode(bImage, bImage, Mat(), Point(-1, -1), 1);
    dilate(bImage, bImage, cv::Mat(), Point(-1, -1), 2);

    vector<vector<Point> > contours;
    findContours(bImage, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_NONE);
    return contours;
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
                circle(dstImage, Point(x, y), 5, Scalar::all(0), -1);
                g_points.push_back(Point(x, y));
            }
        break;
    }

    imshow("dstImage", dstImage);
}