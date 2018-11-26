#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void MakeOriginToCenterUsingRearranging(Mat &src, Mat &dst);
void Printmat(const char *strName, Mat m);

int main()
{
    float dataA[] = {
        1, 2, 4, 5, 2, 1, 
        3, 6, 6, 9, 0, 3,
        1, 8, 3, 7, 2, 5,
        2, 9, 8, 9, 9, 1,
        3, 9, 8, 8, 7, 2,
        4, 9, 9, 9, 9, 3
    };
    Mat A(6, 6, CV_32F, dataA);
    cout<<"A = "<<A<<endl;

    Mat dftA;
    dft(A, dftA, DFT_COMPLEX_OUTPUT);
    MakeOriginToCenterUsingRearranging(dftA, dftA);
    Mat dftA2[2];
    split(dftA, dftA2);

    cout<<"dftA.channels() = "<<endl;
    Printmat("dftA2[0](Re) = ", dftA2[0]);
    Printmat("dftA2[1](Im) = ", dftA2[1]);

    Mat dftB;
    dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
    cout<<"dftB.channels() = "<<dftB.channels()<<endl;
    Printmat("dftB = ", dftB);

    return 0;
}

void MakeOriginToCenterUsingRearranging(Mat &src, Mat &dst)
{
    int cX, cY;
    cX = src.cols/2;
    cY = src.rows/2;

    Mat src1 = src(Rect(0, 0, cX, cY));
    Mat src2 = src(Rect(cX, 0, cX, cY));
    Mat src3 = src(Rect(0, cY, cX, cY));
    Mat src4 = src(Rect(cX, cY, cX, cY));

    Mat dst1 = dst(Rect(0, 0, cX, cY));
    Mat dst2 = dst(Rect(cX, 0,cX, cY));
    Mat dst3 = dst(Rect(0, cY,cX, cY));
    Mat dst4 = dst(Rect(cX, cY, cX, cY));

    if(&src != &dst)
    {
        src1.copyTo(dst4);
        src4.copyTo(dst1);
        src2.copyTo(dst3);
        src3.copyTo(dst2);
    }
    else
    {
        Mat tmp(cX, cY, src.type());
        src1.copyTo(tmp); //swap src1 <-> src4
        src4.copyTo(src1);
        tmp.copyTo(src4);

        src2.copyTo(tmp); //swap src2 <-> src3
        src3.copyTo(src2);
        tmp.copyTo(src3);
    }
}

void Printmat(const char *strName, Mat m)
{
    int x, y;
    float fValue;
    cout<<endl<<strName<<endl;
    cout<<setiosflags(ios::fixed);
    for(y = 0; y < m.rows; y++)
    {
        for(x = 0; x < m.cols; x++)
        {
            fValue = m.at<float>(y, x);
            cout<<setprecision(2)<<setw(8)<<fValue;
        }
        cout<<endl;
    }
    cout<<endl;
}