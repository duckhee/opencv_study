#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void onChange(int pos, void *param);

int main()
{
    Mat image[2];
    image[0] = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(image[0].empty())
    {
        printf("not image\r\n");
        return -1;
    }
    image[1].create(image[0].size(), CV_8U);

    //namedWindow("image");
    imshow("image", image[0]);

    int pos = 128;
    onChange(pos, (void *)image);
    createTrackbar("threshold", "image", &pos, 255, onChange, (void *)image);

    waitKey();

    return 0;
}

//trackbar callback to threshold the image gray value
void onChange(int pos, void *param)
{
    Mat *pMat = (Mat *)param;
    Mat srcImage = Mat(pMat[0]);
    Mat dstImage = Mat(pMat[1]);

    //Direct Thresholding
    int x, y, s, r;
    int nThreshold = pos;

    for(y = 0; y < srcImage.rows; y++)
    {
        for(x = 0; x < srcImage.cols; x++)
        {
            r = srcImage.at<uchar>(y, x);
            if(r > nThreshold)
            {
                s = 255;
            }
            else
            {
                s = 0;
            }
            dstImage.at<uchar>(y, x) = s;
        }
    }
    imshow("image", dstImage);
}