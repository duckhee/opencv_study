#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void lowPassFilterDCT(Mat &A, int n);


int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }

    int nWidth = 8;
    int nHeight = 8;
    int M = srcImage.rows/nHeight;
    int N = srcImage.cols/nWidth;
    int x, y; //left, top
    Rect rtROI;
    Mat roi;
    Mat A, dctA;
    Mat B, dst;
    int n = 1; //1, 5, 20, 0
    Mat dstImage(srcImage.size(), srcImage.type());
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            x = j*nWidth;
            y = i*nHeight;
            rtROI = Rect(x, y, nWidth, nHeight);
            roi = srcImage(rtROI);
            roi.convertTo(A, CV_32F);
            dct(A, dctA);
            lowPassFilterDCT(dctA, n);
            idct(dctA, B);

            B.convertTo(dst, CV_8U);
            dst.copyTo(dstImage(rtROI));
        }
    }
    imshow("dstImage", dstImage);
    waitKey();
    return 0;
    
}

void lowPassFilterDCT(Mat &A, int n)
{
    uchar zigZag[] = { 0, 1, 5, 6, 14, 15, 27, 28,
		2, 4, 7, 13, 16, 26, 29, 42,
		3, 8, 12, 17, 25, 30, 41, 43,
		9, 11, 18, 24, 31, 40, 44, 53,
		10, 19, 23, 32, 39, 45, 52, 54,
		20, 22, 33, 38, 46, 51, 55, 60,
		21, 34, 37, 47, 50, 56, 59, 61,
		35, 36, 48, 49, 57, 58, 62, 63 };
    Mat M(8, 8, CV_8U, zigZag);
    int k;
    for(int v = 0; v < A.rows; v++)
    {
        for(int u = 0; u < A.cols; u++)
        {
            k = M.at<uchar>(v, u);
            if(k>n)
            {
                A.at<float>(v, u) = 0;
            }
        }
    }
    
}
