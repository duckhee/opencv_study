#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void Printmat(const char *strName, Mat A);

int main()
{
    uchar dataA[16] = {
        1, 2, 3, 4, 
        5, 6, 7, 8, 
        9, 10, 11, 12, 
        13, 14, 15, 16
    };
    Mat A(4, 4, CV_8U, dataA);
    Printmat("A = ", A);

    Mat sumA, sqsumA, titledSumA;
    integral(A, sumA, sqsumA, titledSumA);

    Printmat("sumA = ", sumA);
    Printmat("sqsumA = ", sqsumA);
    Printmat("titledSumA = ", titledSumA);

    return 0;

}

void Printmat(const char *strName, Mat A)
{
    int x, y;
    uchar uValue;
    float fValue;
    double dValue;
    int iValue;

    cout<<endl<<endl<<strName<<endl;
    cout<<setiosflags(ios::fixed);
    for(y = 0;  y < A.rows; y++)
    {
        for(x = 0; x < A.cols; x++)
        {
            switch(A.type())
            {
                case CV_8U:
                    uValue = A.at<uchar>(y, x);
                    cout<<setw(8)<<(int)uValue;
                break;
                case CV_32S:
                    iValue = A.at<int>(y, x);
                    cout<<setw(8)<<iValue;
                break;
                case CV_32F:
                    fValue = A.at<float>(y, x);
                    cout<<setprecision(2)<<setw(8)<<fValue;
                break;
                case CV_64F:
                    dValue = A.at<double>(y, x);
                    cout<<setprecision(2)<<setw(8)<<dValue;
                break;
            }
        }
        cout<<endl;
    }
    cout<<endl;
}