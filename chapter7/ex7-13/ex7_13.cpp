#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void ChangeSignOddPositionInXY(Mat &m);
void Printmat(const char *strName, Mat m);

int main()
{
    float dataA[] = {
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 9, 9, 1, 1,
        1, 1, 9, 9, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1
    };

    float lap[] = {
        0, 1, 0, 
        1, -4, 1,
        0, 1, 0
    };

    Mat _A(6, 6, CV_32F, dataA);
    Printmat("_A = ", _A);

    Mat _B(3, 3, CV_32F, lap);
    Printmat("_B = ", _B);

    Mat dstLap;
    filter2D(_A, dstLap, CV_32F, _B, Point(-1, -1), 0.0, BORDER_CONSTANT);
    Printmat("dstLap = ", dstLap);

    //calculate convolution and correlation by DFT
    int nW = getOptimalDFTSize(_A.cols+_B.cols-1);
    int nH = getOptimalDFTSize(_A.rows+_B.rows-1);
    cout<<"nW = "<<nW<<endl;
    cout<<"nH = "<<nH<<endl;
    
    Mat A(nW, nH, CV_32F, Scalar::all(0));
    _A.copyTo(A(Rect(0, 0, _A.cols, _A.rows)));
    Printmat("A = ", A);

    Mat B(nW, nH, CV_32F, Scalar::all(0));
    _B.copyTo(B(Rect(0, 0, _B.cols, _B.rows)));
    Printmat("B = ", B);

    Mat dftA;
    dft(A, dftA, DFT_COMPLEX_OUTPUT);
    Mat dftB;
    dft(B, dftB, DFT_COMPLEX_OUTPUT);

    //convolution
    Mat dftC;
    mulSpectrums(dftA, dftB, dftC, 0); //conjB = false
    dft(dftC, dftC, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
    Printmat("dftC = IDFT(DFT(A)*DFT(B)) = ", dftC);
    Printmat("dftC = dftC(Rect(1, 1, _A.cols-1, _A.rows-1)) = ", dftC(Rect(1, 1, _A.cols-1, _A.rows-1)));
    Printmat("dftC = dftC(Rect(2, 2, _A.cols-2, _A.rowis-2)) = ", dftC(Rect(2, 2, _A.cols-2, _A.rows-2)));

    //correlation
    Mat dftD;
    mulSpectrums(dftA, dftB, dftD, 0, true); //conjB = true
    dft(dftD, dftD, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
    Printmat("dftD = IDFT(DFT(A)*conj(DFT(B))) = ", dftD);
    Printmat("dftD = dftD(Rect(0, 0, _A.cols-2, _A.rows-2)) = ", dftD(Rect(0, 0, _A.cols-2, _A.rows-2)));

    return 0;
}
/*
void ChangeSignOddPositionInXY(Mat &m)
{

}
*/
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
            cout<<setprecision(2)<<setw(6)<<fValue;
        }
        cout<<endl;
    }
    cout<<endl;
}