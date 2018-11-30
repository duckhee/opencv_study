#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    Mat edges;
    Canny(srcImage, edges,50, 100);
    //Canny(srcImage, edges, 50, 200);
    imshow("edges", edges);
    waitKey();
    return -1;
}