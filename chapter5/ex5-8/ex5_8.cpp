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
    
    double minVal, maxVal;
    Point minLoc, maxLoc;

    minMaxLoc(srcImage, &minVal, &maxVal, &minLoc, &maxLoc);
    cout<<"In srcImage"<<endl;
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;
    cout<<"minLoc = "<<minLoc<<endl;
    cout<<"maxLoc = "<<maxLoc<<endl;

    Mat dstImage;
    double scale = 100.0/(maxVal -minVal);
    srcImage.convertTo(dstImage, -1, scale, -scale * minVal);

    minMaxLoc(dstImage, &minVal, &maxVal, &minLoc, &maxLoc);
    cout<<"In dstImage"<<endl;
    cout<<"minVal = "<<minVal<<endl;
    cout<<"maxVal = "<<maxVal<<endl;
    cout<<"minLoc = "<<minLoc<<endl;
    cout<<"maxLoc = "<<maxLoc<<endl;

    imshow("dstImage", dstImage);
    waitKey();

    return 0;

}