#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<float> A(2, 3, 0.0);
    cout<<"A = "<<A<<endl;

    A.create(3, 3);
    
    for(int i = 0; i<A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A(i, j) = (float)(i * A.cols + j);
        }
    }
    cout<<"A = "<<A<<endl;

    A.create(Size(3, 4));
    cout<<"A = "<<A<<endl;

    Mat_<uchar> B;
    int sizes[] = {3, 3};

    B.create(2, sizes);
    cout<<"B = "<<B<<endl;
    return 0;
}