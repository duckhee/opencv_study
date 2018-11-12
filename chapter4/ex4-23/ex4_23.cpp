#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {2, -1, -1, 1};
    float dataB[] = {1, 1, 1, 2};

    Mat A(2, 2, CV_32F, dataA);
    Mat B(2, 2, CV_32F, dataB);
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;

    Mat dst1;
    gemm(A, B, 1.0, noArray(), 0, dst1);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    Mat C = Mat::eye(2, 2, CV_32F);
    gemm(A, B, 2.0, C, 3, dst2);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3 = 2 * A * B + 3 * C;
    cout<<"dst3 = "<<dst3<<endl;

    return 0;
}