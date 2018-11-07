/*
    사진의 평균 화소 값을 표현 해준다.
*/

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);

    float sum = 0;
    MatConstIterator_<uchar> it = srcImage.begin<uchar>();
    for(; it != srcImage.end<uchar>(); it++)
    {
        sum += *it;
    }

    cout<<"Avg = sum / total = "<<sum/srcImage.total()<<endl;

    return 0;
}