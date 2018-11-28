#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void LOG_DFT(Mat &src, Mat &dst, double sigma);
void ZeroCrossing(Mat &src, Mat &dst, int th);
void ChangeSignOddPositionInXY(Mat &m);

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    //Mat srcImage = imread("../rect.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    imshow("srcImage", srcImage);

    Mat src32f;
    srcImage.convertTo(src32f, CV_32F);

    double sigma = 0.01; //0.05, 0.01
    Mat logDst;
    LOG_DFT(src32f, logDst, sigma);

    Mat zeroDst;
    ZeroCrossing(logDst, zeroDst, 1);
    imshow("zeroDest", zeroDst);

    waitKey();

    return 0;
}

void LOG_DFT(Mat &src, Mat &dst, double sigma)
{
    int nW = getOptimalDFTSize(src.cols);
    int nH = getOptimalDFTSize(src.rows);

    Mat A;
    copyMakeBorder(src, A, 0, nH-(src.rows), 0, nW-(src.cols), BORDER_CONSTANT, 0);
    ChangeSignOddPositionInXY(A); //centering
    Mat dftA;
    dft(A, dftA, DFT_COMPLEX_OUTPUT);

    int u, v;
    Vec2f cValue;
    const double phi4 = -4*CV_PI*CV_PI;

    double centerU = dftA.cols/2;
    double centerV = dftA.rows/2;
    double D, G;
    double d = -2*(CV_PI*CV_PI)*sigma*sigma;
    double U, V;

    for(v = 0; v < dftA.rows; v++)
    {
        for(u = 0; u < dftA.cols; u++)
        {
            U = (u-centerU);
            V = (v-centerV);
            D = U*U+V*V;
            cValue = dftA.at<Vec2f>(v, u);

            G = phi4*D*exp(d*D);

            cValue[0] *= G;
            cValue[1] *= G;
            dftA.at<Vec2f>(v, u) = cValue;
        }
    }
    dst.create(src.size(), CV_32F);
    idft(dftA, dst, DFT_SCALE | DFT_REAL_OUTPUT); //dftA.rows
    ChangeSignOddPositionInXY(dst); //centering
}

void ZeroCrossing(Mat &src, Mat &dst, int th)
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
                a = _src(y, x+1);
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
                zeroCrossV.at<float>(y, x) = fabs(a)+fabs(b);
            }
            else
            {
                zeroCrossV.at<float>(y, x) = 0;
            }
        }
    }
    Mat zeroCross(src.size(), CV_32F, Scalar::all(0));
    add(zeroCrossH, zeroCrossV, zeroCross);

    dst.create(src.size(), CV_8U);
    threshold(zeroCross, dst, th, 255, THRESH_BINARY);
}

void ChangeSignOddPositionInXY(Mat &m)
{
    int x, y;
    float fValue;
    for(y = 0; y < m.rows; y++)
    {
        for(x = 0; x< m.cols; x++)
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
