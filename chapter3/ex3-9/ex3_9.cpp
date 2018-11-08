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
    namedWindow("srcImage", WINDOW_NORMAL); //WINDOW_AUTOSIZE
    imshow("srcImage", srcImage);
    waitKey();

    resizeWindow("srcImage", 320, 240);
    waitKey();
    destroyAllWindows();

    return 0;
}