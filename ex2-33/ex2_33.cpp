#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(3, 3, CV_32F, Scalar::all(0));
    cout<<"A = "<<A.size()<<"="<<A<<endl;

    A.resize(2);
    cout<<"A = "<<A.size()<<"="<<A<<endl;

    A.resize(5, Scalar::all(1));
    cout<<"A = "<<A.size()<<"="<<A<<endl;

    A.reserve(10);
    cout<<"A = "<<A.size()<<"="<<A<<endl;

    A.release();
    cout<<"A = "<<A.size()<<"="<<A<<endl;

    return 0;
}