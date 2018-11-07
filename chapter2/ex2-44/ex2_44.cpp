#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<Vec3b> srcImage;
    srcImage.create(512, 512);

    for(int i = 0; i < srcImage.rows; i++)
    {
        for(int j = 0; j < srcImage.cols; j++)
        {
            srcImage(i, j) = Vec3f(255, 255, 255);
        }
    }

    imshow("srcImage", srcImage);

    waitKey();
    return 0;
}