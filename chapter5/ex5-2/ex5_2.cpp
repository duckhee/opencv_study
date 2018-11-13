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
    //Mat lut(1, 256, CV_8U);
    /*
    for(int i = 0; i < 256; i++)
    {
        lut.at<uchar>(o, i) = 256 -i;
    }
    */

   Mat_<uchar> lut(1, 256);
   for(int i = 0; i < 256; i++)
   {
       lut(i) = 256 - i;
   }
   Mat dstImage;
   LUT(srcImage, lut, dstImage);
   imshow("dstImage", dstImage);
   waitKey();

   return 0;
}