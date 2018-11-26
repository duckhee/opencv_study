#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat &m);
void Printmat(const char *strName, Mat m);

int main()
{
    float dataA[] = {
        1, 2, 4, 5, 2, 1,
        3, 6, 6, 9, 0, 3,
        1, 8, 3, 7, 2, 5,
        2, 9, 8, 9, 9, 1,
        3, 9 ,8 ,8, 7, 2,
        4, 9, 9, 9, 9, 3
    };
    Mat A(6, 6, CV_32F, dataA);
    cout<<"A = "<<A<<endl;
    ChangeSignOddPositionInXY(A); //cenering
    Mat dftA;
    dft(A, dftA, DFT_COMPLEX_OUTPUT);

    Mat dftA2[2];
    split(dftA, dftA2);

    cout<<"dftA.channels() = "<<dftA.channels()<<endl;
    Printmat("dftA2[0](Re) = ", dftA2[0]);
    Printmat("dftA2[1](Im) = ", dftA2[1]);

    Mat dftB;
    dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
    ChangeSignOddPositionInXY(dftB); //centering

    cout<<"dftB.channels() = "<<dftB.channels()<<endl;
    Printmat("dftB = ", dftB);

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
            //if((x+y)%2 == 1 && fValue != 0)
            if((x+y)%2 == 1) //odd number
            {
                m.at<float>(y, x) = -fValue;
            }
        }
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