#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void ChangeOddPositionInXY(Mat &m);

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    Mat fImage;
    srcImage.convertTo(fImage, CV_32F);
    ChangeOddPositionInXY(fImage); //centering

    Mat dftA;
    dft(fImage, dftA, DFT_COMPLEX_OUTPUT);

    Mat dftA2[2];
    split(dftA, dftA2);

    Mat magF;
    magnitude(dftA2[0], dftA2[1], magF);
    magF += Scalar(1);
    log(magF, magF);

    double minValue, maxValue;
    minMaxLoc(magF, &minValue, &maxValue);
    cout<<"minValue = "<<minValue<<endl;
    cout<<"maxValue = "<<maxValue<<endl;

    Mat magImage;
    normalize(magF, magImage, 0, 255, NORM_MINMAX, CV_8U);
    imshow("magImage", magImage);

    Mat angleF;
    phase(dftA2[0], dftA2[1], angleF);
    
    Mat angleImage;
    normalize(angleF, angleImage, 0, 255, NORM_MINMAX, CV_8U);
    imshow("angleImage", angleImage);
    waitKey();

    return 0;



    return 0;
}

void ChangeOddPositionInXY(Mat &m)
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