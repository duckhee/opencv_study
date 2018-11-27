#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Point PhaseCorr(Mat &_A, Mat &_B, double *maxloc);

int main()
{
    Mat srcImage = imread("alphabet.bmp",  IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    String tName[] = {"A.bmp", "s.bmp", "b.bmp", "m.bmp"};

    Mat dstImage;
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

    Mat src32f;
    srcImage.convertTo(src32f, CV_32F);
    cout<<"src32f.size() = "<<src32f.size()<<endl;
    for(int i = 0; i < 4; i++)
    {
        Mat tImage = imread(tName[i], IMREAD_GRAYSCALE);
        if(tImage.empty())
        {
            return -1;
        }
        cout<<"template : "<<tName[i]<<endl;
        Mat tmpl32f;
        tImage.convertTo(tmpl32f, CV_32F);

        double phaseCorr;
        Point peakLoc = PhaseCorr(src32f, tmpl32f, &phaseCorr);
        cout<<"phaseCorr = "<<phaseCorr<<endl;
        cout<<"peakLoc = "<<peakLoc<<endl;
        rectangle(dstImage, Point((int)peakLoc.x, (int)peakLoc.y), Point(peakLoc.x+tImage.cols, peakLoc.y+tImage.rows), Scalar(255, 0, 0), 2);
    }
    imshow("dstImage", dstImage);
    waitKey();
    return 0;
        
}

Point PhaseCorr(Mat &_A, Mat &_B, double *maxValue)
{
    //calculate convolution and correlation by DFT
    int nW = getOptimalDFTSize(_A.cols + _B.cols - 1);
    int nH = getOptimalDFTSize(_A.rows + _B.rows - 1);

    Mat A;
    copyMakeBorder(_A, A, 0, nH-(_A.rows), 0, nW-(_A.cols), BORDER_CONSTANT, 0);
    Mat B;
    copyMakeBorder(_B, B, 0, nH-(_B.rows), 0, nW-(_B.cols), BORDER_CONSTANT, 0);

    //correlation magF = IDFT(DFT(A)*conj(DFT(B)))
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
    //Printmat("Corr=", magF);

    Point peakLoc;
    minMaxLoc(magF, NULL, maxValue, NULL, &peakLoc);
    return peakLoc;
}