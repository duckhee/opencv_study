#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<float> A(10, 10);

    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A(i, j) = (float)(i * A.cols + j);
        }
    }

    cout<<"A = "<<A<<endl;
    cout<<"sum(A) = "<<sum(A)<<endl;

    float sum2 = 0;
    Mat_<float>::iterator it = A.begin();

    for(; it != A.end(); it++)
    {
        sum2 += *it;
    }
    printf("sum2 = %f\n", sum2);

    Mat_<float> B(10, 10);
    Mat_<float>::const_iterator itA = A.begin();
    Mat_<float>::iterator itB = B.begin();

    for(; itA != A.end(); itA++, itB++)
    {
        *itB = *itA;
    }

    cout<<"B = "<<B<<endl;

    return 0;
}