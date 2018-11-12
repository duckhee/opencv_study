#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    //2D
    float dataM1[] = {1, 0, 0, 0, 1, 0, 0, 0, 2};
    Mat M1(3, 3, CV_32F, dataM1);
    cout<<"M1 = "<<M1<<endl;

    Point arr1 = Point(200, 100);
    Mat A1(1, 1, CV_32FC2, Scalar(arr1.x, arr1.y));
    cout<<"A1 = "<<A1<<endl;

    Mat dst1;
    perspectiveTransform(A1, dst1, M1);
    cout<<"dst1 = "<<dst1<<endl;

    //3D
    Point3f arr2 = Point3f(200, 100, 1);
    Mat M2 = Mat::eye(4, 4, CV_32F);
    M2.at<float>(3, 3) = 2;
    cout<<"M2 = "<<M2<<endl;

    Mat A2(1, 1, CV_32FC3, Scalar(arr2.x, arr2.y, arr2.z));
    cout<<"A2 = "<<A2<<endl;

    Mat dst2;
    perspectiveTransform(A2, dst2, M2);
    cout<<"dst2 = "<<dst2<<endl;

    return 0;
}