#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void FirstDerivativeGauss(Mat &src, Mat &dst, double sigma, int dir);
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

    double sigma = 0.01; //0. 05, 0.03, 0.01, 0.005
    Mat dX;
    FirstDerivativeGauss(src32f, dX, sigma, 0);

    Mat dY;
    FirstDerivativeGauss(src32f, dY, sigma, 1);

    //Mat zeros = Mat::zeros(src32f.size(), CV_32F);
    Mat mag32f;
    //magnitude(dX, zeros, mag32f);
    mag32f = abs(dX);
    Mat magX;
    normalize(mag32f, magX, 0, 255, NORM_MINMAX, CV_8U);
    imshow("magX", magX);

    //magnitude(zeros, dY, mag32f);
    mag32f = abs(dY);
    Mat magY;
    normalize(mag32f, magY, 0, 255, NORM_MINMAX, CV_8U);
    imshow("magY", magY);

    magnitude(dX, dY, mag32f);
    Mat magXY;
    normalize(mag32f, magXY, 0, 255, NORM_MINMAX, CV_8U);
    imshow("magXY", magXY);

    waitKey();
    return 0;

}

void FirstDerivativeGauss(Mat &src, Mat &dst, double sigma, int dir)
{
    int nW = getOptimalDFTSize(src.cols);
    int nH = getOptimalDFTSize(src.rows);

    Mat A;
    copyMakeBorder(src, A, 0, nH-(src.rows), 0, nW-(src.cols), BORDER_CONSTANT, 0);

    ChangeSignOddPositionInXY(A); //centering
    Mat dftA;
    dft(A, dftA, DFT_COMPLEX_OUTPUT);

    int u, v;
    Vec2f aValue, cValue1, cValue2;
    const double phi2 = 2*CV_PI;

    double centerU = dftA.cols/2;
    double centerV = dftA.rows/2;
    double D, G;
    double d = -2*(CV_PI*CV_PI)*sigma*sigma;
    double U, V;

    for(v = 0; v < dftA.rows; v++)
    {
        for(u = 0; u <dftA.cols; u++)
        {
            U = (u-centerU);
            V = (v-centerV);
            D = U*U+V*V;
            cValue1 = dftA.at<Vec2f>(v, u);
            if(dir == 0)
            {
                G = exp(d*D)*phi2*U;
            }
            else
            {
                G = exp(d*D)*phi2*V;
            }
            cValue2[0] = 0.0;
            cValue2[1] = G;
            aValue[0] = (cValue1[0]*cValue2[0]-cValue1[1]*cValue2[1]);
            aValue[1] = (cValue1[0]*cValue2[1]+cValue1[1]*cValue2[0]);
            dftA.at<Vec2f>(v, u) = aValue;
        }
    }
    dst.create(src.size(), CV_32F);
    idft(dftA, dst, DFT_SCALE | DFT_REAL_OUTPUT); //dftA.rows);
    ChangeSignOddPositionInXY(dst); //centering
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
