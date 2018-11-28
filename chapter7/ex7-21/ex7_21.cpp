#include <iomanip>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void lowPassFilterDCT(Mat &A, int n);
void Printmat(const char *strName, Mat A);

int main()
{
	float dataA[] = {   56, 55, 61, 66, 70, 61, 64, 73,
						63, 59, 55, 90, 109, 85, 69, 72,
						62, 59, 68, 113, 144, 104, 66, 73,
						63, 58, 71, 122, 154, 106, 70, 69,
						67, 61, 68, 104, 126, 88, 68, 70,
						79, 65, 60, 70, 77, 68, 58, 75,
						85, 71, 64, 59, 55, 61, 65, 83,
						87, 79, 69, 68, 65, 76, 78, 94 };
    Mat A(8, 8, CV_32F, dataA);
    Printmat("A = ", A);

    Mat dctA;
    dct(A, dctA);
    Printmat("dctA=", dctA);

    lowPassFilterDCT(dctA, 5); //5, 10, 20, 50
    Printmat("dctA=", dctA);

    Mat B;
    idct(dctA, B);
    //dct(dctA, B, DCT_INVERSE);
    Printmat("B=", B);

    return 0;

}

void lowPassFilterDCT(Mat &A, int n)
{
	uchar zigZag[] = { 0, 1, 5, 6, 14, 15, 27, 28,
		2, 4, 7, 13, 16, 26, 29, 42,
		3, 8, 12, 17, 25, 30, 41, 43,
		9, 11, 18, 24, 31, 40, 44, 53,
		10, 19, 23, 32, 39, 45, 52, 54,
		20, 22, 33, 38, 46, 51, 55, 60,
		21, 34, 37, 47, 50, 56, 59, 61,
		35, 36, 48, 49, 57, 58, 62, 63 };
    
    Mat M(8, 8, CV_8U, zigZag);
    //cout<<"M = "<<M<<endl;
    int k;
    for(int v = 0; v < A.rows; v++)
    {
        for(int u = 0; u < A.rows; u++)
        {
            k = M.at<uchar>(v, u);
            if(k>n)
            {
                A.at<float>(v, u) = 0;
            }
        }
    }
}

void Printmat(const char *strName, Mat A)
{
    int x, y;
    float fValue;
    cout<<endl<<endl<<strName<<endl;
    cout<<setiosflags(ios::fixed);
    for(y = 0; y < A.rows; y++)
    {
        for(x = 0; x < A.cols; x++)
        {
            fValue = A.at<float>(y, x);
            cout<<setprecision(2)<<setw(8)<<fValue;
        }
        cout<<endl;
    }
    cout<<endl;
}
