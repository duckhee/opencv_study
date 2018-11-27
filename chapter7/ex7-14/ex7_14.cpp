#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void Printmat(const char *strName, Mat m);
Point PhaseCorr(Mat &_A, Mat &_B, double *maxloc);

int main()
{
    float dataA[] = {
        1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 
        1, 1, 9, 9, 1, 1, 
        1, 1, 9, 9, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
    };
    float dataB[] = {
        9, 9, 1,
        9, 9, 1,
        1, 1, 1
    };

    float dataB2[] = {
        1, 1, 1,
        1, 9, 9, 
        1, 9, 9
    };

    Mat A(6, 6, CV_32F, dataA);
    Printmat("A = ", A);
    Mat B(3, 3, CV_32F, dataB);
    //Mat B(3, 3, CV_32F, dataB2);
    Printmat("B = ", B);
    double phaseCorr;
    Point peakLoc = PhaseCorr(A, B, &phaseCorr);
    cout<<"phaseCorr = "<<phaseCorr<<endl;
    cout<<"peakLoc = "<<peakLoc<<endl;

    return 0;

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

Point PhaseCorr(Mat &_A, Mat &_B, double *maxValue)
{
    //calculate convolution and correlation by DFT
    int nW = getOptimalDFTSize(_A.cols+_B.cols-1);
    int nH = getOptimalDFTSize(_A.rows+_B.rows-1);
    
    Mat A;
    copyMakeBorder(_A, A, 0, nH-(_A.rows), 0, nW-(_A.cols), BORDER_CONSTANT, 0);
    Mat B;
    copyMakeBorder(_B, B, 0, nH-(_B.rows), 0, nW-(_B.cols), BORDER_CONSTANT, 0);

    //Mat A(nW, nH, CV_32F, Scalar::all(0));
    //_A.copyTo(A(Rect(0, 0, _A.cols, _A.rows)));
    //Mat B(nW, nH, CV_32F, Scalar::all(0));
    //_B.copyTo(B(Rect(0, 0, _B.cols, _B.rows)));

    //correlation: magF = IDFT(DFT(A)*conj(DFT(B)))
    Mat dftA;
    dft(A, dftA, DFT_COMPLEX_OUTPUT);
    Mat dftB;
    dft(B, dftB, DFT_COMPLEX_OUTPUT);

    Mat dftD;
    mulSpectrums(dftA, dftB, dftD, 0, true); //conjB = true

    Mat matCmplx[2];
    split(dftD, matCmplx);
    //normalize by magnitude
    Mat magF;
    magnitude(matCmplx[0], matCmplx[1], magF);
    divide(matCmplx[0], magF, matCmplx[0]);
    divide(matCmplx[1], magF, matCmplx[1]);
    //matCmplx[0] /= magF;
    //matCmplx[1] /= magF;
    merge(matCmplx, 2, dftD);

    dft(dftD, magF, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
    //magF : phase correlation
    Printmat("Corr = ", magF);
    
    Point peakLoc;
    minMaxLoc(magF, NULL, maxValue, NULL, &peakLoc);
    return peakLoc;
}