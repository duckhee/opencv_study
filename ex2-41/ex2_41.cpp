#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat_<Vec3f> image(400, 400, Vec3b(255, 255, 255));

    for(int i = 0; i < 400; i++)
    {
        image(i, i) = Vec3b(0, 0, 0);
    }

    for(int i = 0; i <image.rows; i++)
    {
        for(int j = 0; j<image.cols; j++)
        {
            image(i, j)[0] = 0;
        }
    }

    imshow("image", image);
    waitKey();

    return 0;
}