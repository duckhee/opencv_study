#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);

    if(srcImage.empty())
    {
        return -1;
    }

    Size ksize(7, 7); //ksize(21, 21);
    Mat avgKernel = Mat::ones(ksize, CV_32F);
    avgKernel /= avgKernel.total();
    //cout<<"avgKernel.total() = "<<avgKernel.total()<<endl;
    //cout<<"avgKernel = "<<avgKernel<<endl;
    Mat avgImage;
    filter2D(srcImage, avgImage, -1, avgKernel);
    imshow("avgImage", avgImage);

    Mat avgX = Mat::ones(1, ksize.width, CV_32F);
    Mat avgY = Mat::ones(ksize.height, 1, CV_32F);
    avgX /= avgX.total();
    avgY /= avgY.total();
    //cout<<"avgX = "<<avgX<<endl;
    //cout<<"avgY = "<<avgY<<endl;

    Mat avgImage2;
    sepFilter2D(srcImage, avgImage2, -1, avgX, avgY);
    imshow("avgImage2", avgImage2);

    waitKey();

    return 0;

}