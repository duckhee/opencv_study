#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Matx16f A = Matx16f::randu(0.0, 1.0);
    Matx16f B = Matx16f::randu(0.0,1.0);

    cout<<"A="<<(Mat)A<<endl;
    cout<<"B="<<(Mat)B<<endl;

    Matx23f C = A.reshape<2,3>();
    cout<<"C="<<(Mat)C<<endl;
    
}