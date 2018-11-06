#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(4, 5, CV_32FC3);
    cout<<"A.rows = "<<A.rows<<endl;
    cout<<"A.cols = "<<A.cols<<endl;
    cout<<"A.dims = "<<A.dims<<endl;
    //cout<<"A.retcount = "<<A.refcout<<endl;

    Mat B = A;
    //cout<<"*A.refcount = "<<*A.refcount<<endl;
    //cout<<"*B>refcount = "<<*B.refcount<<endl;

    A.at<Vec3f>(0,0) = Vec3f(0.75, 1.0, 10.0);
    cout<<"A.data = "<<hex<<(int *)A.data<<endl;
    cout<<"B.data = "<<hex<<(int *)B.data<<endl;
    
    cout<<"A.data[0] = "<<*(float *)A.data<<endl;
    cout<<"A.data[4] = "<<*(float *)(A.data + 4)<<endl;
    cout<<"A.data[8] = "<<*(float *)(A.data + 8)<<endl;

    cout<<"B.data[0] = "<<*(float *)B.data<<endl;
    cout<<"B.data[4] = "<<*(float *)(B.data + 4)<<endl;
    cout<<"B.data[8] = "<<*(float *)(B.data + 8)<<endl;

    cout<<"A.isContinuous() = "<<A.isContinuous()<<endl;
    cout<<"A.total() = "<<dec<<A.total()<<endl;
    cout<<"A.elemSize() = "<<A.elemSize()<<endl;
    cout<<"A.elemSize1() = "<<A.elemSize1()<<endl;
    cout<<"A.type() = "<<A.type()<<endl;
    cout<<"A.depth() = "<<A.depth()<<endl;
    cout<<"A.channels() = "<<A.channels()<<endl;

    cout<<"A.step = "<<A.step<<endl;
    cout<<"A.step1() = "<<A.step1()<<endl;
    cout<<"A.empty() = "<<A.empty()<<endl;
    cout<<"A.size() = "<<A.size()<<endl;

    return 0;
}