#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void detectHScolor(const Mat &image, double minHue, double maxHue, double minSat, double maxSat, Mat &mask);

int main()
{
    Mat image = imread("./BALLOON2.png");
    if(image.empty())
    {
        printf("no image\r\n");
        return -1;
    }
    Mat mask;
    detectHScolor(image, 100, 150, 15, 255, mask);
    //Hue range(100~150) Saturation range(15~255) mask set
    Mat detected(image.size(), CV_8UC3, Scalar::all(0));
    image.copyTo(detected, mask);
    //마스크에 원본 벡터를 투과 시켜 걸러냄
    namedWindow("Image");
    imshow("Image", image);
    namedWindow("Mask");
    imshow("Mask", mask);
    namedWindow("Detected");
    imshow("Detected", detected);
    waitKey();

    return 0;
}

void detectHScolor(const Mat &image, double minHue, double maxHue, double minSat, double maxSat, Mat &mask)
{
    Mat hsv;
    cvtColor(image, hsv, CV_BGR2HSV);
    vector<Mat> channels;
    split(hsv, channels); //hsv channel 분리
    //Hue mask(0 ~255)
    Mat mask1;
    threshold(channels[0], mask1, maxHue, 255, THRESH_BINARY_INV);
    Mat mask2;
    threshold(channels[0], mask2, minHue, 255, THRESH_BINARY);
    Mat hueMask;
    if(minHue<maxHue)
    {
        hueMask = mask1 & mask2;
    }
    else{
        hueMask = mask1 | mask2;
    }

    threshold(channels[1], mask1, maxSat, 255, THRESH_BINARY_INV);
    threshold(channels[1], mask2, minSat, 255, THRESH_BINARY);

    Mat satMask;
    satMask = mask1 & mask2;
    //ballone copy
    mask = hueMask & satMask;

}