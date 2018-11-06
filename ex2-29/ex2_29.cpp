#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(3, 3, CV_32F); //CV_32FC!
    for(int i = 0; i < A.rows; i++)
    {
        float* ptrA = A.ptr<float>(i);
        for(int j = 0; j < A.cols; j++)
        {
            //A.at<float>(i, j) = i * A.cols + j;
            ptrA[j] = i * A.cols + j;
        }
    }

    cout<<"A = "<<A<<endl;

    return 0;
}