#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Matx33f A = Matx33f::zeros();
    Matx33f B = Matx33f::ones();
    Matx33f C = Matx33f::eye();
    Matx33f D = Matx33f::all(10.0);

    cout<<"A="<<(Mat)A<<endl;
    cout<<"B="<<(Mat)B<<endl;
    cout<<"C="<<(Mat)C<<endl;
    cout<<"D="<<(Mat)D<<endl;
}