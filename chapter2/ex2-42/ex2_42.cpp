#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<uchar> srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);

    float sum = 0;

    for(int i = 0; i < srcImage.rows; i++)
    {
        for(int j = 0; j < srcImage.cols; j++)
        {
            sum += srcImage(i, j);
        }
    }
    cout<<"Avg = sum/total = "<<sum/srcImage.total()<<endl;

    waitKey();

    return 0;
}