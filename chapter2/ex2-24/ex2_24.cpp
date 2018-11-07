#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage;
    srcImage.create(512, 512, CV_8UC3);

    for(int i = 0; i < srcImage.rows; i++)
    {
        for(int j = 0; srcImage.cols; j++)
        {
            srcImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
        }
    }

    imshow("srcImage", srcImage);
    waitKey();
    return 0;
}