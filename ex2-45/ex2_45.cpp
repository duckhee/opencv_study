#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<Vec3f> A(4, 5, Vec3f(255, 255, 255));
    cout<<"A.rows = "<<A.rows<<endl;
    cout<<"A.cols = "<<A.cols<<endl;
    cout<<"A.dims = "<<A.dims<<endl;
    cout<<"A.size() = "<<A.size()<<endl;
    cout<<"A.total() = "<<A.total()<<endl;

    cout<<"A.elemSize() = "<<A.elemSize()<<endl;
    cout<<"A.elemSize1() = "<<A.elemSize1()<<endl;
    cout<<"A.type() = "<<A.type()<<endl;
    cout<<"A.depth() = "<<A.depth()<<endl;
    cout<<"A.channels() = "<<A.channels()<<endl;

    cout<<"A.step = "<<A.step<<endl;
    cout<<"A.steop1() = "<<A.step1()<<endl;
    cout<<"A.stepT() = "<<A.stepT()<<endl;

    return 0;

}