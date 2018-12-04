#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

vector<vector<Point> > myFindContours(Mat &srcImage);

int main()
{
    Mat refImage = imread("../refShapes.jpg", IMREAD_GRAYSCALE);
    if(refImage.empty())
    {
        printf("no refShapes.jpg image \r\n");
        return -1;
    }Mat testImage = imread("../testShapes1.jpg", IMREAD_GRAYSCALE);
    if(testImage.empty())
    {
        printf("no testShapes1.jpg image \r\n");
        return -1;
    }
    Scalar colorTable[] = {
        Scalar(0, 0, 255),
        Scalar(0, 255, 0),
        Scalar(255, 0, 0)
    };
    vector<vector<Point> > refContours = myFindContours(refImage);
    vector<vector<Point> > testContours = myFindContours(testImage);
    cout<<"refContours.size() = "<<refContours.size()<<endl;
    cout<<"testContours.size() = "<<testContours.size()<<endl;

    if(refContours.size() < 1 || testContours.size() < 1)
    {
        return 0;
    }

    Mat refRGB;
    cvtColor(refImage, refRGB, COLOR_GRAY2BGR); //CV_GRAY2BGR
    for(int k = 0; k < refContours.size(); k++)
    {
        drawContours(refRGB, refContours, k, colorTable[k], 2);
    }
    imshow("refRGB", refRGB);

    Mat testRGB;
    cvtColor(testImage, testRGB, COLOR_GRAY2BGR);

    int minK;
    double minD;
    int method = 3; //CV_CONTOURS_MATH_I3 in "types_c.h"
    for(int i = 0; i < testContours.size(); i++)  //matching testContours
    {
        //find matches
        minK = 0;
        minD = matchShapes(refContours[0], testContours[i], method, 0);
        for(int k = 1; k < refContours.size(); k++)
        {
            double d = matchShapes(refContours[k], testContours[i], method, 0);
            //cout<<"K = "<<k<<", d = "<<d<<endl;
            if(d < minD)
            {
                minD = d;
                minK = k;
            }
        }
        drawContours(testRGB, testContours, i, colorTable[minK], 2);
        cout<<"minK = "<<minK<<endl;
        //imshow("testRGB", testRGB);
        //waitKey(0);
    }
    imshow("testRGB", testRGB);
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