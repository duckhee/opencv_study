#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Ptr<IplImage> Image(cvLoadImage("lena.jpg", IMREAD_GRAYSCALE));
    if(Image.empty())
    {
        return -1;
    }
    cvSaveImage("lena.bmp", Image);
    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
    cvShowImage("Image", Image);
    cvWaitKey(0);
    cvDestroyAllWindows();
    return 0;
}