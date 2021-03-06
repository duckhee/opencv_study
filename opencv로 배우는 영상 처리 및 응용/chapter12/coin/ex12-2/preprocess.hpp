#ifndef __PREPROCESS_H__
#define __PREPROCESS_H__

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void draw_rotatedRect(Mat &img, RotatedRect mr, Scalar color, int thickness = 2)
{
    Point2f pts[4];
    mr.points(pts);

    for(int i = 0; i < 4; i++)
    {
        line(img, pts[i], pts[(i+1)%4], color, thickness);
    }
}

Mat preprocessing(Mat img)
{
    Mat gray, th_img;
    cvtColor(img, gray, CV_BGR2GRAY);
    GaussianBlur(gray, gray, Size(7, 7), 2, 2);

    threshold(gray, th_img, 130, 255, THRESH_BINARY | THRESH_OTSU);
    morphologyEx(th_img, th_img, MORPH_OPEN, Mat(), Point(-1, -1), 1);

    return th_img;
}

vector<RotatedRect> find_coins(Mat img)
{
    vector<vector<Point> >contours;
    findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<RotatedRect> circles;
    for(int i = 0; i < (int)contours.size(); i++)
    {
        RotatedRect mr = minAreaRect(contours[i]);
        mr.angle = (mr.size.width + mr.size.height)/4.0f;

        if(mr.angle > 18)
        {
            circles.push_back(mr);
        }
    }

    return circles;
}

#endif