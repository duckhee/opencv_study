#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void zeroCrossing(Mat &src, Mat &dst, int threshold);

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    //Mat srcImage = imread("../rect.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    const int ksize = 9;
    float logArr[ksize * ksize];
    int s, t, k = 0;
    float g;
    //float sigma = 1.4f;
    float sigma = 0.3f * (ksize / 2 -1.0f) + 0.8f;
    for(s = -ksize/2; s <= ksize/2; s++)
    {
        for(t = -ksize/2; t <= ksize/2; t++)
        {
            g = exp(-((float)s * s + (float)t*t)/(2*sigma *sigma));
            g *= (1-((float)s*s + (float)t*t)/(2*sigma *sigma));
            g /= (3.141592f*sigma*sigma*sigma*sigma);
            logArr[k++] = -g;
        }
    }
    Mat logKernel(ksize, ksize, CV_32F, logArr);
    cout<<"logKernel = "<<logKernel<<endl;

    Mat logImage;
    filter2D(srcImage, logImage, CV_32F, logKernel);

    Mat dstImage;
    zeroCrossing(logImage, dstImage, 1);

    imshow("dstImage", dstImage);
    waitKey();
    return 0;
}

void zeroCrossing(Mat &src, Mat &dst, int th)
{
    int x, y;
    double a, b;
    Mat zeroCrossH(src.size(), CV_32F, Scalar::all(0));
    Mat_<float> _src(src);
    for(y = 1; y < src.rows-1; y++)
    {
        for(x = 1; x < src.cols-1; x++)
        {
            a = _src(y, x);
            b = _src(y, x+1);
            if(a == 0)
            {
                a = _src(y, x-1);
            }
            if(a*b < 0)
            {
                zeroCrossH.at<float>(y, x) = fabs(a) + fabs(b);
            }
            else{
                zeroCrossH.at<float>(y, x) = 0;
            }
        }
    }
    
    Mat zeroCrossV(src.size(), CV_32F, Scalar::all(0));
    for(y = 1; y < src.rows-1; y++)
    {
        for(x = 1; x < src.cols-1; x++)
        {
            a = _src(y, x);
            b = _src(y+1, x);
            if(a == 0)
            {
                a = _src(y-1, x);
            }
            if(a*b < 0)
            {
                zeroCrossV.at<float>(y, x) = fabs(a) + fabs(b);
            }
            else
            {
                zeroCrossV.at<float>(y, x) = 0;
            }
        }
    }
    Mat zeroCross(src.size(), CV_32F, Scalar::all(0));
    add(zeroCrossH, zeroCrossV,zeroCross);
    threshold(zeroCross, dst, th, 255, THRESH_BINARY);
}