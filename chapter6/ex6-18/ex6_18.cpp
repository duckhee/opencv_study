#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

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
    float dataB[] = {
        9, 9, 1, 
        9, 9, 1, 
        1, 1, 1
    };
    Mat A(6, 6, CV_32F, dataA);
    Printmat("A = ", A);

    Mat B(3, 3, CV_32F, dataB);
    Printmat("B = ", B);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    Mat result;

    //TM_SQDIFF
    matchTemplate(A, B, result, TM_SQDIFF); //CV_TM_SQDIFF
    Printmat("result:TM_SQDIFF = ", result);
    minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
    cout<<"minVal = "<<minVal<<endl;
    cout<<"minLoc = "<<minLoc<<endl;

    //TM_CCORR
    matchTemplate(A, B, result, TM_CCORR); //CV_TM_CCORR_NORMED
    Printmat("result:TM_CCORR = ", result);
    minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
    cout<<"maxVal = "<<maxVal<<endl;
    cout<<"maxLoc = "<<maxLoc<<endl;

    //TM_CCORR_NORMED
    matchTemplate(A, B, result, TM_CCORR_NORMED); //CV_TM_CCORR_NORMED
    Printmat("result:TM_CCORR_NORMED = ", result);
    minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
    cout<<"maxVal = "<<maxVal<<endl;
    cout<<"maxLoc = "<<maxLoc<<endl;

    //TM_CCOEFF
    matchTemplate(A, B, result, TM_CCOEFF); //CV_TM_CCOEFF
    Printmat("result:TM_CCOEFF = ", result);
    minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
    cout<<"maxVal = "<<maxVal<<endl;
    cout<<"maxLoc = "<<maxLoc<<endl;

    //TM_CCOEFF_NORMED
    matchTemplate(A, B, result, TM_CCOEFF_NORMED);
    Printmat("result:TM_CCOEFF_NORMED = ", result);
    minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
    cout<<"maxVal = "<<maxVal<<endl;
    cout<<"maxLoc = "<<maxLoc<<endl;

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
        for(x = 0; x< m.cols; x++)
        {
            fValue = m.at<float>(y, x);
            cout<<setprecision(2)<<setw(8)<<fValue;
        }
        cout<<endl;
    }
    cout<<endl;
}