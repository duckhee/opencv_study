#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(3, 3, CV_32FC3);
    for(int i = 0; i < A.rows; i++)
    {
        Vec3f* ptrA = A.ptr<Vec3f>(i);
        for(int j = 0; j < A.cols; j++)
        {
            ptrA[j] = Vec<float, 3>(255, 0, i * A.cols + j);
        }
    }
    cout<<"A = "<<A<<endl;

    Mat B(3, 3, CV_32FC3);
    for(int i = 0; i < A.rows; i++)
    {
        float* ptrB = B.ptr<float>(i);
        for(int j = 0; j < A.cols; j++)
        {
            ptrB[j*3] = 255;
            ptrB[j*3 + 1] = 0;
            ptrB[j*3 + 2] = i * B.cols +j;
        }
    }

    cout<<"B = "<<B<<endl;

    return 0;
}