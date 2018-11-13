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
    add(fImage, Scalar(1), fImage);

    Mat logImage;
    log(fImage, logImage);

    double minVal, maxVal;
    minMaxLoc(logImage, &minVal, &maxVal);
    cout<<"Before normalizing in logImage"<<endl;
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;

    normalize(logImage, logImage, 0, 1.0, NORM_MINMAX);
    minMaxLoc(logImage, &minVal, &maxVal);
    cout<<"After normalizing in logImage"<<endl;
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;
    
    imshow("logImage", logImage);
    waitKey();

    return 0;
}