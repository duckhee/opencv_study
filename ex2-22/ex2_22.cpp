#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Ptr<IplImage> oldImage(cvLoadImage("lena.jpg", IMREAD_GRAYSCALE));
    if(oldImage.empty())
    {
        return -1;
    }

    Mat newImage = cvarrToMat(oldImage);

    imshow("newImage", newImage);
    waitKey();
    return 0;
}