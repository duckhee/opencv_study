#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void Printmat(const char *strName, Mat m);
// source :/sources//modules/imgproc/src/phasecorr.cpp
static void magSpectrums(InputArray _src, OutputArray _dst)
{
    Mat src = _src.getMat();
    int depth = src.depth(), cn = src.channels(), type = src.type();
    int rows = src.rows, cols = src.cols;
    int j, k;

    CV_Assert(type == CV_32FC1 || type == CV_32FC2 || type ==CV_64FC1 || type == CV_64FC2);

    if(src.depth() == CV_32F)
    {
        _dst.create(src.rows, src.cols, CV_32FC1);
    }
    else{
        _dst.create(src.rows, src.cols, CV_64FC1);
    }

    Mat dst = _dst.getMat();
    dst.setTo(0); //Mat elements are not equal to zero by default!

    bool is_1d = (rows == 1 || (cols == 1 && src.isContinuous() && dst.isContinuous()));

    if(is_1d)
    {
        cols = cols + rows -1, rows = 1;
    }

    int ncols = cols*cn;
    int j0 = cn == 1;
    int j1 = ncols - (cols % 2 == 0 && cn == 1);

    if(depth == CV_32F)
    {
        const float *dataSrc = (const float*)src.data;
        float* dataDst = (float*)dst.data;

        size_t stepSrc = src.step/sizeof(dataSrc[0]);
        size_t stepDst = dst.step/sizeof(dataDst[0]);

        if(!is_1d && cn == 1)
        {
            for(k = 0; k < (cols % 2 ? 1: 2); k++)
            {
                if(k == 1)
                {
                    dataSrc += cols-1, dataDst += cols-1;
                }
                dataDst[0] = dataSrc[0]*dataSrc[0];
                if(rows%2 == 0)
                {
                    dataDst[(rows-1)*stepDst] = dataSrc[(rows-1)*stepSrc]*dataSrc[(rows-1)*stepSrc];
                }
                for(j = 1; j <= rows - 2; j+= 2)
                {
                    dataDst[j&stepDst] = (float)std::sqrt((double)dataSrc[j*stepSrc]*dataSrc[j*stepSrc] + 
                        (double)dataSrc[(j+1)*stepSrc] * dataSrc[(j+1)*stepSrc]);
                }
                if(k == 1)
                {
                    dataSrc -= cols-1, dataDst -= cols-1;
                }
            }
            for(; rows--; dataSrc += stepSrc, dataDst += stepDst)
            {
                if(is_1d && cn == 1)
                {
                    dataDst[0] = dataSrc[0]*dataSrc[0];
                    if(cols % 2 == 0)
                    {
                        dataDst[j1] = dataSrc[j1]*dataSrc[j1];
                    }
                }
                for(j = j0; j < j1; j+= 2)
                {
                    dataDst[j] = (float)std::sqrt((double)dataSrc[j]*dataSrc[j] + (double)dataSrc[j+1]*dataSrc[j+1]);
                }
            }
        }
        else
        {
            const double *dataSrc = (const double*)src.data;
            double *datatDst = (double *)dst.data;

            size_t stepSrc = src.step/sizeof(dataSrc[0]);
            size_t stepDst = dst.step/sizeof(dataDst[0]);

            if(!is_1d && cn == 1)
            {
                for(k = 0; k < (cols % 2 ? 1 : 2); k++)
                {
                    if(k == 1)
                    {
                        dataSrc += cols - 1, dataDst += cols - 1;
                    }
                    dataDst[0] = dataSrc[0] * dataSrc[0];
                    if(rows % 2 == 0)
                    {
                        dataDst[(rows-1)*stepDst] = dataSrc[(rows-1)*stepSrc] *dataSrc[(rows-1)*stepSrc];
                    }
                    for(j = 1; j <= rows - 2; j += 2)
                    {
                        dataDst[j*stepDst] = std::sqrt(dataSrc[j*stepSrc]*dataSrc[j*stepSrc] + 
                            dataSrc[(j+1)*stepSrc]*dataSrc[(j+1)*stepSrc]);
                    }
                    if(k == 1)
                    {
                        dataSrc -= cols - 1, dataDst -= cols - 1;
                    }
                }
            }
            for(; rows--; dataSrc += stepSrc, dataDst += stepDst)
            {
                if(is_1d && cn == 1)
                {
                    dataDst[0] = dataSrc[0] * dataSrc[0];
                    if(cols % 2 == 0)
                    {
                        dataDst[j1] = dataSrc[j1]*dataSrc[j1];
                    }
                }
                for(j = j0; j < j1; j += 2)
                {
                    dataDst[j] = std::sqrt(dataSrc[j]*dataSrc[j]+dataSrc[j+1]*dataSrc[j+1]);
                }
            }
        }
    }
}

static void divSpectrums(InputArray _srcA, InputArray _srcB, OutputArray _dst, int flags, bool conjB)
{
    Mat srcA = _srcA.getMat(), srcB = _srcB.getMat();
    int depth = srcA.depth(), cn = srcA.channels(), type = srcA.type();
    int rows = srcA.rows, cols = srcA.cols;
    int j, k;

    CV_Assert(type == srcB.type() && srcA.size() == srcB.size());
    CV_Assert(type == CV_32FC1 || type == CV_32FC2 || type == CV_64FC1 || type == CV_64FC2);

    _dst.create(srcA.rows, srcA.cols, type);
    Mat dst = _dst.getMat();

    bool is_1d = (flags & DFT_ROWS) || (rows == 1 || (cols == 1 && srcA.isContinuous() && srcB.isContinuous() && dst.isContinuous()));

    if(is_1d && !(flags & DFT_ROWS))
    {
        cols = cols + rows -1, rows = 1;
    }
    int ncols = cols*cn;
    int j0 = cn ==1;
    int j1 = ncols - (cols % 2 == 0 && cn == 1);

    if(depth == CV_32F)
    {
        const float *dataA = (const float *)srcA.data;
        const float *dataB = (const float *)srcB.data;
        float *dataC = (float *)dst.data;
        float eps = FLT_EPSILON; //prevent div problems

        size_t stepA = srcA.step/sizeof(dataA[0]);
        size_t stepB = srcB.step/sizeof(dataB[0]);
        size_t stepC = dst.step/sizeof(dataC[0]);

        if(!is_1d && cn == 1)
        {
            for(k = 0; k < (cols % 2 ? 1 : 2); k++)
            {
                if(k == 1)
                {
                    dataA += cols-1, dataB += cols-1, dataC += cols-1;
                }
                dataC[0] = dataA[0]/(dataB[0]+eps);
                if(rows % 2 == 0)
                {
                    dataC[(rows-1)*stepC] = dataA[(rows-1)*stepA]/(dataB[(rows-1)*stepB]+eps);
                }
                if(!conjB)
                {
                    for(j = 1; j <= rows - 2; j+= 2)
                    {
                        double denom = (double)dataB[j*stepB]*dataB[j*stepB] +
                            (double)dataB[(j+1)*stepB]*dataB[(j+1)*stepB] + (double)eps;
                            
                        double re = (double)dataA[j*stepA]*dataB[j*stepB] +
                            (double)dataA[(j+1)*stepA]*dataB[(j+1)*stepB];

                        double im = (double)dataA[(j+1)*stepA]*dataB[j*stepB] -
                            (double)dataA[j*stepA]*dataB[(j+1)*stepB];

                        dataC[j*stepC] = (float)(re / denom);
                        dataC[(j+1)*stepC] = (float)(im / denom);
                    }
                }
                else
                {
                    for(j = 1; j <= rows -2; j += 2)
                    {
                        double denom = (double)dataB[j*stepB]*dataB[j*stepB] + 
                            (double)dataB[(j+1)*stepB]*dataB[(j+1)*stepB]+(double)eps;

                        double re = (double)dataA[j*stepA]*dataB[j*stepB] - 
                            (double)dataA[(j+1)*stepA] * dataB[(j+1)*stepB];

                        double im = (double)dataA[(j+1)*stepA]*dataB[j*stepB] + 
                            (double)dataA[j*stepA]*dataB[(j+1)*stepB];

                        dataC[j*stepC] = (float)(re / denom);
                        dataC[(j+1)*stepC] = (float)(im / denom);
                    }
                }
                if(k == 1)
                {
                    dataA -= cols -1, dataB -= cols - 1 , dataC -= cols - 1;
                }
            }
        }
        
        for(; rows--; dataA += stepA, dataB += stepB, dataC += stepC)
        {
            if(is_1d && cn == 1)
            {
                dataC[0] = dataA[0] / (dataB[0] + eps);
                if(cols % 2 == 0)
                {
                    dataC[j1] = dataA[j1] / (dataB[j1] + eps);
                }
            }
            if(!conjB)
            {
                for(j = j0; j < j1; j += 2)
                {
                    double denom = (double)(dataB[j]*dataB[j] + dataB[j+1]*dataB[j+1]+eps);
                    double re = (double)(dataA[j]*dataB[j] + dataA[j+1]*dataB[j+1]);
                    double im = (double)(dataA[j+1]*dataB[j] - dataA[j]*dataB[j+1]);
                    dataC[j] = (float)(re / denom);
                    dataC[j+1] = (float)(im / denom);
                }
            }
            else
            {
                for(j = j0; j < j1; j+= 2)
                {
                    double denom = (double)(dataB[j]*dataB[j] + dataB[j+1]*dataB[j+1]+eps);
                    double re = (double)(dataA[j]*dataB[j] - dataA[j+1]*dataB[j+1]);
                    double im = (double)(dataA[j+1]*dataB[j] + dataA[j]*dataB[j+1]);
                    dataC[j] = (float)(re / denom);
                    dataC[j+1] = (float)(im / denom);
                }
            }
        }
    }
    else
    {
        const double *dataA = (const double *)srcA.data;
        const double *dataB = (const double *)srcB.data;
        double *dataC = (double *)dst.data;
        double eps = DBL_EPSILON; //prevent div0 problems

        size_t stepA = srcA.step / sizeof(dataA[0]);
        size_t stepB = srcB.step / sizeof(dataB[0]);
        size_t stepC = dst.step / sizeof(dataC[0]);

        if(!is_1d && cn == 1)
        {
            for(k = 0; k < (cols % 2 ? 1 : 2); k++)
            {
                if(k == 1)
                {
                    dataA += cols - 1, dataB += cols - 1, dataC += cols - 1;
                }
                dataC[0] = dataA[0] / (dataB[0] + eps);
                if(rows % 2 == 0)
                {
                    dataC[(rows - 1) * stepC] = dataA[(rows - 1) * stepA] / (dataB[(rows - 1) * stepB] + eps);
                }
                if(!conjB)
                {
                    for(j = 1 ; j <= rows - 2; j += 2)
                    {
                        double denom = dataB[j*stepB]*dataB[j*stepB] + 
                            dataB[(j + 1)*stepB]*dataB[(j+1)*stepB] + eps;

                        double re = dataA[j*stepA]*dataB[j*stepB] + 
                            dataA[(j+1)*stepA]*dataB[(j+1)*stepB];

                        double im = dataA[(j+1)*stepA]*dataB[j*stepB] -
                            dataA[j*stepA]*dataB[(j+1)*stepB];

                        dataC[j*stepC] = re / denom;
                        dataC[(j+1)*stepC] = im /denom;
                    }
                }
                else
                {
                    for(j = 1; j <= rows - 2; j += 2)
                    {
                        double denom = dataB[j*stepB]*dataB[j*stepB] +
                            dataB[(j+1)*stepB]*dataB[(j+1)*stepB] + eps;

                        double re = dataA[j*stepA]*dataB[j*stepB] - 
                            dataA[(j+1)*stepA] * dataB[(j+1)*stepB];

                        double im = dataA[(j+1)*stepA]*dataB[j*stepB] + 
                            dataA[j*stepA]*dataB[(j+1)*stepB];

                        dataC[j*stepC] = re / denom;
                        dataC[(j+1)*stepC] = im / denom;
                    }
                }
                if(k == 1)
                {
                    dataA -= cols - 1, dataB -= cols - 1, dataC -= cols - 1;
                }
            }
        }
        for(; rows--; dataA += stepA, dataB += stepB, dataC += stepC)
        {
            if(is_1d && cn == 1)
            {
                dataC[0] = dataA[0] / (dataB[0] + eps);
                if(cols % 2 == 0)
                {
                    dataC[j1] = dataA[j1]/(dataB[j1] + eps);
                }
            }
            if(!conjB)
            {
                for(j = j0; j < j1; j += 2)
                {
                    double denom = dataB[j]*dataB[j]+dataB[j+1]*dataB[j+1] + eps;
                    double re = dataA[j]*dataB[j] + dataA[j+1]*dataB[j+1];
                    double im = dataA[j+1]*dataB[j] - dataA[j] * dataB[j+1];
                    dataC[j] = re / denom;
                    dataC[j+1] = im / denom;
                }
            }
            else 
            {
                for(j = j0; j < j1; j += 2)
                {
                    double denom = dataB[j]*dataB[j] + dataB[j+1] *dataB[j+1] + eps;
                    double re = dataA[j]*dataB[j] - dataA[j+1] * dataB[j+1];
                    double im = dataA[j+1] * dataB[j] + dataA[j]* dataB[j+1];
                    dataC[j] = re / denom;
                    dataC[j+1] = im / denom;
                }
            }
        }
    }
}

static Point2d weightedCentroid(InputArray _src, cv::Point peakLocation, cv::Size weightBoxSize, double *response)
{
    Mat src = _src.getMat();

    int type = src.type();
    CV_Assert(type == CV_32FC1 || type == CV_64FC1);

    int minr = peakLocation.y - (weightBoxSize.height >> 1);
    int maxr = peakLocation.y + (weightBoxSize.height >> 1);
    int minc = peakLocation.x - (weightBoxSize.width >> 1);
    int maxc = peakLocation.x + (weightBoxSize.width >> 1);

    Point2d centroid;
    double sumIntensity = 0.0;

    //clamp the values to min and max if needed.
    if(minr < 0)
    {
        minr = 0;
    }
    if(minc < 0)
    {
        minc = 0;
    }
    if(maxr > src.rows - 1)
    {
        maxr = src.rows -1;
    }
    if(maxc > src.cols -1)
    {
        maxc = src.cols -1;
    }
    if(type == CV_32FC1)
    {
        const float *dataIn = (const float *)src.data;
        dataIn += minr*src.cols;
        for(int y = minr; y <= maxr; y++)
        {
            for(int x = minc; x <= maxc; x++)
            {
                centroid.x += (double)x*dataIn[x];
                centroid.y += (double)y*dataIn[x];
                sumIntensity += (double)dataIn[x];
            }
            dataIn += src.cols;
        }
    }
    else
    {
        const double *dataIn = (const double *)src.data;
        dataIn += minr*src.cols;
        for(int y = minr; y <= maxr; y++)
        {
            for(int x = minc; x <= maxc; x++)
            {
                centroid.x += (double)x*dataIn[x];
                centroid.y += (double)y*dataIn[x];
                sumIntensity += dataIn[x];
            }
            dataIn += src.cols;
        }
    }
    if(response)
    {
        *response = sumIntensity;
    }
    sumIntensity += DBL_EPSILON; //prevent div0 problems ...

    centroid.x /= sumIntensity;
    centroid.y /= sumIntensity;

    return centroid;
}

Point2d MyphaseCorrelateRes(InputArray _src1, InputArray _src2, InputArray _window, double *response)
{
    Mat src1 = _src1.getMat();
    Mat src2 = _src2.getMat();
    Mat window = _window.getMat();

    CV_Assert(src1.type() == src2.type());
    CV_Assert(src1.type() == CV_32FC1 || src1.type() == CV_64FC1);
    CV_Assert(src1.size == src2.size);

    if(!window.empty())
    {
        CV_Assert(src1.type() == window.type());
        CV_Assert(src1.size == window.size);
    }

    int M = getOptimalDFTSize(src1.rows);
    int N = getOptimalDFTSize(src1.cols);

    Mat padded1, padded2, paddedWin;

    if(M != src1.rows || N != src1.cols)
    {
        copyMakeBorder(src1, padded1, 0, M-src1.rows, 0, N-src1.cols, BORDER_CONSTANT, Scalar::all(0));
        copyMakeBorder(src2, padded2, 0, M-src2.rows, 0, N-src2.cols, BORDER_CONSTANT, Scalar::all(0));

        if(!window.empty())
        {
            copyMakeBorder(window, paddedWin, 0, M-window.rows, 0, N-window.cols, BORDER_CONSTANT, Scalar::all(0));
        }
    }
    else
    {
        padded1 = src1;
        padded2 = src2;
        paddedWin = window;
    }

    Mat FFT1, FFT2, P, Pm, C;

    //perform window multiplication if available
    if(!paddedWin.empty())
    {
        //apply window to both images before preceeding...
        multiply(paddedWin, padded1, padded1);
        multiply(paddedWin, padded2, padded2);
    }
    //execute phase correlation equation
    //Reference : http://en.wikipedia.org/wiki/Phase_correlation
    dft(padded1, FFT1, DFT_REAL_OUTPUT);
    dft(padded2, FFT2, DFT_REAL_OUTPUT);

    mulSpectrums(FFT1, FFT2, P, 0, true);

    magSpectrums(P, Pm);
    divSpectrums(P, Pm, C, 0, false); // FF* / | FF* |

    idft(C, C); //give us the nice peak shift location ...
    //KDK: C = IDFT(FF* / | FF* |)
    //(phase correlation equation completed here...)

    //modify by KDK
    //fftShift(C); //shift the energy to the center of the frame.

    //locate the highest peak
    Point peakLoc;
    minMaxLoc(C, NULL, NULL, NULL, &peakLoc);

    //get the phase shift with sub-pixel accracy,
    //5x5 widow seems about right here...
    Point2d t;
    t = weightedCentroid(C, peakLoc, Size(5, 5), response);

    //modify by KDK
    //return (center - t);

    return peakLoc;
}
//end of phasecorr.cpp

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

    float dataB3[] = {
        1, 1, 1,
        9, 9, 1,
        9, 9, 1
    };

    Mat A(6, 6, CV_32F, dataA);
    Printmat("A = ", A);
    //Mat B(3, 3, CV_32F, dataB1);
    //Mat B(3, 3, CV_32F, dataB2);
    Mat B(3, 3, CV_32F, dataB3);
    Printmat("B = ", B);

    int nW = getOptimalDFTSize(A.cols + B.cols -1);
    int nH = getOptimalDFTSize(A.rows + B.rows -1);
    //cout<<"nW = "<<nW<<endl;
    //cout<<"nH = "<<nH<<endl;

    Mat A2;
    copyMakeBorder(A, A2, 0, nH-A.rows, 0, nW-A.cols, BORDER_CONSTANT, 0);
    Mat B2;
    copyMakeBorder(B, B2, 0, nH-B.rows, 0, nW-B.cols, BORDER_CONSTANT, 0);

    double phaseCorr1;

    //OpenCV3.1.0
    Point2d peakLoc1 = phaseCorrelate(A2, B2, noArray(), &phaseCorr1);
    cout<<"phaseCorr1 = "<<phaseCorr1<<endl;
    cout<<"peakLoc1 = "<<peakLoc1<<endl<<endl;

    double phaseCorr2;
    Point2d peakLoc2 = MyphaseCorrelateRes(A2, B2, noArray(), &phaseCorr2);
    cout<<"phaseCorr2 = "<<phaseCorr2<<endl;
    cout<<"peakLoc2 = "<<peakLoc2<<endl<<endl;
    return 0;

}

void Printmat(const char *strName, Mat m)
{
    int x, y;
    float fValue;

    cout<<endl<<endl<<strName<<endl;
    cout<<setiosflags(ios::fixed);
    for(y = 0; y < m.rows; y++)
    {
        for(x = 0; x < m.cols ; x++)
        {
            fValue = m.at<float>(y, x);
            cout<<setprecision(2)<<setw(8)<<fValue;

        }
        cout<<endl;
    }
    cout<<endl;
}