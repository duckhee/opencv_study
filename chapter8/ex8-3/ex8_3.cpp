#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage = imread("./line.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }

    Mat edges;
    Canny(srcImage, edges, 50, 100);
    imshow("edges", edges);

    //Mat line
    vector<Vec4i> lines;
    HoughLinesP(edges, lines, CV_PI/180.0, 10, 30, 10);

    Mat dstImage(srcImage.size(), CV_8UC3);
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
    Vec4i params;
    int x1, y1, x2, y2;
    //for(int k = 0; k < lines.cols; k++)
    for(int k = 0; k < lines.size(); k++)
    {
        //params = lines.at<Vec4i>(0, k);
        params  = lines[k];
        x1 = params[0];
        y1 = params[1];
        x2 = params[2];
        y2 = params[3];
        printf("lines[%2d] = P1(%4d, %4d) = P2(%4d, %4d)\n", k, x1, y1, x2, y2);

        //drawing a line segment
        Point pt1(x1, y1), pt2(x2, y2);
        line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);
    }
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}