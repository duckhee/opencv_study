#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* param);

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    imshow("dstImage", dstImage);
    setMouseCallback("dstImage", onMouse, (void *)&dstImage);

    waitKey();

    return 0;
}


void onMouse(int event, int x, int y, int flags, void* param)
{
    Mat *pMat = (Mat *)param;
    Mat image = Mat(*pMat);
    switch(event)
    {
        case EVENT_LBUTTONDOWN:
            if(flags & EVENT_FLAG_SHIFTKEY)
            {
                rectangle(image, Point(x - 5, y - 5), Point(x + 5, y + 5), Scalar(255, 0, 0));
            }
            else
            {
                circle(image, Point(x, y), 5, Scalar(0, 0, 255), 5);
            }
        break;
        case EVENT_RBUTTONDOWN:
            circle(image, Point(x, y), 5, Scalar(255, 0, 0),  5);
        break;
        case EVENT_LBUTTONDBLCLK:
            image =Scalar(255, 255, 255);
        break;
    }

    imshow("dstImage", image);

    return 0;
}