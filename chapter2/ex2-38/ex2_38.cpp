#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A;
    Mat row = Mat::ones(1, 3, CV_32F);
    A.push_back(row);
    cout<<"A.size() = "<<A.size()<<endl;
    cout<<"A.type() = "<<A.type()<<endl;
    cout<<"A = "<<A<<endl;

    A.push_back((Mat)Mat::zeros(1, 3, CV_32F));
    A.push_back((Mat)Mat::ones(1, 3, CV_32F));
    A.push_back((Mat)Mat(Vec3f(10.0f, 20.0f, 30.0f)).t());
    cout<<"A = "<<A.size()<<"="<<A<<endl;

    A.pop_back();
    cout<<"A = "<<A.size()<<" = "<<A<<endl;
    A.pop_back(2);
    cout<<"A = "<<A.size()<<" = "<<A<<endl;

    Mat B;
    B.push_back(10);
    B.push_back(20);
    B.push_back(30);
    B.push_back(40);
    cout<<"B.size() = "<<B.size()<<endl;
    cout<<"B.type() = "<<B.type()<<endl;
    cout<<"B = "<<B<<endl;

    Mat C;
    C.push_back(10.0f);
    C.push_back(20.0f);
    C.push_back(30.0f);
    C.push_back(40.0f); //C.push_back(40); //type error
    cout<<"C.size() = "<<C.size()<<endl;
    cout<<"C.type() = "<<C.type()<<endl;
    cout<<"C = "<<C<<endl;

    C.pop_back();
    cout<<"C = "<<C.size()<<" = "<<C<<endl;
    C.pop_back(2);
    cout<<"C = "<<C.size()<< " = "<<C<<endl;

    return 0;
}