#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat &m);
void GaussianSmoothDFT(Mat &src, Mat &dst, double sigma);

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

    Mat dstGauss;
    double sigma = 0.005; //0.1, 0.05, 0.01, 0.005
    GaussianSmoothDFT(src32f, dstGauss, sigma);

    Mat magImage;
    dstGauss.convertTo(magImage, CV_8U);
    imshow("magImage", magImage);
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

void GaussianSmoothDFT(Mat &src, Mat &dst, double sigma)
{
    int nW = getOptimalDFTSize(src.cols);
    int nH = getOptimalDFTSize(src.rows);

    Mat A;
    copyMakeBorder(src, A, 0, nH-(src.rows), 0, nW-(src.cols), BORDER_CONSTANT, 0);

    ChangeSignOddPositionInXY(A); //center
    Mat dftA;
    dft(A, dftA, DFT_COMPLEX_OUTPUT);

    int u, v;
    Vec2f cmplxValue;
    double centerU = dftA.cols/2;
    double centerV = dftA.rows/2;
    double d = -2*(CV_PI*CV_PI)*sigma*sigma;
    double U, V, D, G;

    for(v = 0; v < dftA.rows; v++)
    {
        for(u = 0; u < dftA.cols; u++)
        {
            U = (u-centerU);
            V = (v-centerV);
            D = U*U+V*V;
            cmplxValue = dftA.at<Vec2f>(v, u);

            G = exp(d*D);
            cmplxValue[0] *= G;
            cmplxValue[1] *= G;
            dftA.at<Vec2f>(v, u) = cmplxValue;
        }
    }
    dst.create(src.size(), CV_32F);
    idft(dftA, dst, DFT_SCALE | DFT_REAL_OUTPUT, dftA.rows);
    ChangeSignOddPositionInXY(dst); //centering
    
}