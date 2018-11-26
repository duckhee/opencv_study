#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("alphabet.bmp", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    Mat tImage1 = imread("A.bmp", IMREAD_GRAYSCALE);
    Mat tImage2 = imread("S.bmp", IMREAD_GRAYSCALE);
    Mat tImage3 = imread("b.bmp", IMREAD_GRAYSCALE);
    Mat tImage4 = imread("m.bmp", IMREAD_GRAYSCALE);
    if(tImage1.empty() || tImage2.empty() || tImage3.empty() || tImage4.empty())
    {
        return -1;
    }

    Mat dstImage;
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    Mat result;

    //TM_SQDIFF
    matchTemplate(srcImage, tImage1, result, TM_SQDIFF);
    minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
    rectangle(dstImage, minLoc, Point(minLoc.x + tImage1.cols, minLoc.y+tImage1.rows), Scalar(255, 0, 0), 2);

    //TM_SQDIFF_NORMED
    matchTemplate(srcImage, tImage2, result, TM_SQDIFF_NORMED);
    minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
    rectangle(dstImage, minLoc, Point(minLoc.x+tImage2.cols, minLoc.y+tImage2.rows), Scalar(0, 255, 0), 2);

    //TM_CCORR_NORMED
    matchTemplate(srcImage, tImage3, result, TM_CCORR_NORMED);
    minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
    rectangle(dstImage, maxLoc, Point(maxLoc.x+tImage3.cols, maxLoc.y+tImage4.rows), Scalar(0, 0, 255), 2);

    //TM_CCOEFF_NORMED
    matchTemplate(srcImage, tImage4, result, TM_CCOEFF_NORMED);
    minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
    rectangle(dstImage, maxLoc, Point(maxLoc.x+tImage4.cols, maxLoc.y+tImage4.rows), Scalar(255, 0, 255), 2);

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
    

}