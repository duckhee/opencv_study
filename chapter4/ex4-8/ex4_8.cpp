#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    //uchar dataA[] = {0, 50, 100, 150, 200, 255};
    //Mat A(2, 3, CV_8U, dataA);
    Mat A = (Mat_<uchar>(2, 3) << 0, 50, 100, 150, 200, 255);
    cout<<"A = "<<A<<endl;

    //Mat lut(1, 256, CV_8U);
    /*
    for(int i = 0; i < 256; i++)
    {
        lut.at<uchar>(0, i) = 255 -i;    
    }
    */
    Mat_<uchar> lut(1, 256);
    for(int i = 0; i < 256; i++)
    {
        lut(i) = 255 -i;
    }
    cout<<"lut = "<<lut<<endl;

    Mat dst;
    LUT(A, lut, dst);
    cout<<"dst = "<<dst<<endl;

    return 0;
}