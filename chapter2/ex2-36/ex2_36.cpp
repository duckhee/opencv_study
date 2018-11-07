#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(10, 10, CV_32F);

    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A.at<float>(i, j) = (float)(i * A.cols + i);
        }
    }

    cout<<"A = "<<A<<endl;
    cout<<"sum(A) = "<<sum(A)<<endl;

    float sum2 = 0;

    MatConstIterator_<float> it = A.begin<float>();

    for(; it != A.end<float>(); it++)
    {
        sum2 += *it;
    }
    printf("sum2 = %f\n", sum2);
    
    Mat B(10, 10, CV_32F);
    MatConstIterator_<float> itA = A.begin<float>();
    MatIterator_<float> itB = B.begin<float>();

    for(; itA != A.end<float>(); itA++, itB++)
    {
        *itB = *itA;
    }

    cout<<"B = "<<B<<endl;

    return 0;
}