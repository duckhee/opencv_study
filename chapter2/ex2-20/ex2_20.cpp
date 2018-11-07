#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Vec<float, 3> V(1, 0, 0);
    Mat V1(V);
    Mat V2(Vec<float, 3>(0, 1, 0));
    cout<<"V1 = "<<V1<<endl;
    cout<<"V2 = "<<V2<<endl;
    
    Matx<float, 3, 3> A(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat A1(A);
    cout<<"A1 = "<<A1<<endl;

    Mat A2(A1, Range(1, 2), Range::all());
    cout<<"A2 = "<<A2<<endl;

    Mat A3(A1, Rect(1, 1, 2, 2));
    cout<<"A3"<<A3<<endl;

    CvMat mat = cvMat(3, 3, CV_32FC1, A.val);
    Mat A4 = cvarrToMat(&mat); //copyData = false
    A.val[0] = 100;

    cout<<"A = "<<A<<endl;
    cout<<"A4 = "<<A4<<endl;

    Mat A5 = cvarrToMat(&mat, true); //copyData = true
    A.val[0] = 200;
    cout<<"A = "<<A<<endl;
    cout<<"A5 = "<<A5<<endl;

    return 0;
}