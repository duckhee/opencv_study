#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    vector<Point3f> V1;
    V1.push_back(Point3f(255, 0, 0));
    V1.push_back(Point3f(0, 255, 0));
    V1.push_back(Point3f(0, 0, 255));
    V1.push_back(Point3f(0, 255, 255));

    Mat A(V1);
    //Mat A(4, 1, CV_32FC3);
    //memcpy(A.data, V1.data(), V1.size() * sizeof(Point3f)); //copy vector to mat
    cout<<"A.channels() = "<<A.channels()<<endl;
    cout<<"A.rows = "<<A.rows<<endl;
    cout<<"A.cols = "<<A.cols<<endl;
    cout<<"A = "<<A<<endl;
    
    vector<Point3f> V2;
    A.copyTo(V2);
    //V2.assign((Point3f *)A.datastart, (Point3f*)A.dataend);

    cout<<"V2 = ";
    for(int i = 0; i < V2.size(); i++)
    {
        cout<<(Point3f)V2[i]<<", ";
    }
    cout<<endl;

    Mat B = A.reshape(1);
    Mat C = A.reshape(1).t(); //B.t()

    cout<<"B.channels() = "<<B.channels()<<endl;
    cout<<"B.rows = "<<B.rows<<endl;
    cout<<"B.cols = "<<B.cols<<endl;
    cout<<"B = "<<B<<endl;

    cout<<"C.channels() = "<<C.channels()<<endl;
    cout<<"C.rows = "<<C.rows<<endl;
    cout<<"C.cols = "<<C.cols<<endl;
    cout<<"C = "<<C<<endl;

    return 0;
}