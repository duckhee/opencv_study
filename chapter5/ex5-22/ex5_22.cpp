#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../fruits.jpg");
    if(srcImage.empty())
    {
        return -1;
    }

    Mat hsvImage;
    cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
    vector<Mat> planes;
    split(hsvImage, planes);
    Mat hueImage = planes[0];

    Rect roi(100, 100, 100, 100); //yellow orange
    //Rect roi(400, 150, 100, 100); //green kiwi
    rectangle(srcImage, roi, Scalar(0 ,0, 255), 2);
    Mat roiImage = hueImage(roi);

    int histSize = 256;
    float hValue[] = {0, 256};
    const float* ranges[] = {hValue};
    int channels = 0;
    int dims = 1;

    Mat hist;
    calcHist(&roiImage, 1, &channels, Mat(), hist, dims, &histSize, ranges);
    //cout<<"hsit = "<<hist<<endl;

    Mat hueImage2;
    hueImage.convertTo(hueImage2, CV_32F);

    Mat backProject;
    calcBackProject(&hueImage2, 1, &channels, hist, backProject, ranges);

    double minVal, maxVal;
    minMaxLoc(backProject, &minVal, &maxVal);
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;

    Mat backProject2;
    normalize(backProject, backProject2, 0, 255, NORM_MINMAX, CV_8U);
    //Mat dstImage;
    //int th = threshold(backProject, dstImage, maxVal*0.6, 255, THRESH_BINARY);
    //int th =threshold(backProject2, dstImage, 120, 255, THRESH_BINARY + THRESH_OTSU);
    //cout<<"th = ">>th<<endl;

    imshow("backProject2", backProject2);
    imshow("srcImage", srcImage);
    //imshow("dstImage", dstImage);
    waitKey();

    return 0;


}