#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {-2, 2, -3, -1, 1, 3, 2, 0, -1};
    Mat A(3, 3, CV_32F, dataA);
    cout<<"A = "<<A<<endl;
    cout<<"trace(A) = "<<trace(A)<<endl;

    Mat tA;
    transpose(A, tA);
    cout<<"tA = "<<tA<<endl;
    double det = determinant(A);
    cout<<"det(A) = "<<det<<endl;

    return 0;
}