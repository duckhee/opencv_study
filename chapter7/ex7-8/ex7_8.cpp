#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat &m);
void ButterworthLowpassFilteringH(Mat F, double D0, int n);

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }

    Mat fImage;
    srcImage.convertTo(fImage, CV_32F);
    ChangeSignOddPositionInXY(fImage); //centering

    Mat dftA;
    dft(fImage, dftA, DFT_COMPLEX_OUTPUT);

    double D0 = 5.0; //30, 80, 200
    int n = 2;
    ButterworthLowpassFilteringH(dftA, D0, n);
    Mat dftB;
    dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
    ChangeSignOddPositionInXY(dftB);

    Mat dstImage;
    dftB.convertTo(dstImage, CV_8U);
    imshow("dstImage", dstImage);

    waitKey();
    return 0;
}

void ChangeSignOddPositionInXY(Mat &m)
{
    int x, y;
    float fValue;
    for(y = 0; y < m.rows; y++)
    {
        for(x = 0; x < m.cols; x++)
        {
            fValue = m.at<float>(y, x);
            //if((x+y)%2 == 1) //odd number
            if((x+y)%2 == 1 && fValue != 0)
            {
                m.at<float>(y, x) = -fValue;
            }
        }
    }
}

void ButterworthLowpassFilteringH(Mat F, double D0, int n)
{
    int u, v;
    double D; //distance
    double H;
    double centerU = F.cols/2;
    double centerV = F.rows/2;
    Vec2f cmplxValue;

    //filter H
    for(v = 0; v < F.rows; v++)
    {
        for(u = 0; u < F.cols; u++)
        {
            D = sqrt((u-centerU)*(u-centerU) + (v-centerV)*(v-centerV));
            H = 1.0/(1.0+pow(D/D0, 2*n));

            cmplxValue = F.at<Vec2f>(v, u);
            cmplxValue.val[0] *= H;
            cmplxValue.val[1] *= H;
            F.at<Vec2f>(v, u) = cmplxValue;
        }
    }
}