#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    Mat fImage;
    srcImage.convertTo(fImage, CV_32F);
    
    double power = 4;
    Mat powImage;
    pow(fImage, power, powImage);

    double minVal, maxVal;
    minMaxLoc(powImage, &minVal, &maxVal);
    cout<<"Before normalizing in powImage"<<endl;
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;

    normalize(powImage, powImage, 0, 1.0, NORM_MINMAX);
    minMaxLoc(powImage, &minVal, &maxVal);
    cout<<"After normalizing in powImage"<<endl;
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;

    imshow("powImage",powImage);
    waitKey();
    

    return 0;
}