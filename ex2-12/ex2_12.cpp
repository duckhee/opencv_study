#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Vec<float, 3> X(1, 0, 0);
    Vec<float, 3> Y(0, 1, 0);
    Vec3f Z = X.cross(Y);
    cout<<"X="<<(Mat)X<<endl;
    cout<<"Y="<<(Mat)Y<<endl;
    cout<<"Z=X.cross(Y)="<<(Mat)Z<<endl;

    Point3f pt3 = X;
    cout<<"pt3 = "<<pt3<<endl;

    X = Vec3f(1, 2, 3);
    Y = Vec3f(10, 100, 1000);
    Z = X.mul(Y);

    cout<<"X="<<X<<endl;
    cout<<"Y="<<Y<<endl;
    cout<<"Z=X.mul(Y)="<<Z<<endl;

    cout<<"sum(Z)="<<sum(Z)<<endl;
    cout<<"dotProduct="<<sum(Z)(0)<<endl;

    X=Vec3f::all(0.0);
    cout<<"X="<<X<<endl;

    return 0;
}