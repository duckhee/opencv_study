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
    imshow("srcImage", srcImage);

    Size size(5, 5);
    Mat rectKernel = getStructuringElement(MORPH_RECT, size);
    cout<<"retKernel = "<<rectKernel<<endl;
    int iterations = 3;
    Point archor(-1, -1);
    Mat erodeImage;
    erode(srcImage, erodeImage, rectKernel, archor, iterations);
    imshow("errodImage", erodeImage);

    Mat ellipseKernel = getStructuringElement(MORPH_ELLIPSE, size);
    cout<<"ellipseKernel = "<<ellipseKernel<<endl;

    Mat erodeImage2;
    erode(srcImage, erodeImage2, ellipseKernel, archor, iterations);
    imshow("erodeImage2", erodeImage2);

    Mat dilateImage2;
    dilate(srcImage, dilateImage2, ellipseKernel, archor, iterations);
    imshow("dilateImage2", dilateImage2);

    Mat crossKernel = getStructuringElement(MORPH_CROSS, size);
    cout<<"crossKernel = "<<crossKernel<<endl;

    Mat erodeImage3;
    erode(srcImage, erodeImage3, crossKernel, archor, iterations);
    imshow("erodeImage3", erodeImage3);

    Mat dilateImage3;
    dilate(srcImage, dilateImage3, crossKernel, archor, iterations);
    imshow("dilateImage3", dilateImage3);

    waitKey();

    return 0;
}