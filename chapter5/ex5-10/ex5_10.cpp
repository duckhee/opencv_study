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
    int histSize = 32;
    float valueRange[] = {0, 256};
    const float* ranges[] = {valueRange};
    int channels = 0;
    int dims = 1;

    Mat hist;
    calcHist(&srcImage, 1, &channels, Mat(), hist, 1, &histSize, ranges);

    Mat histImage(512, 512, CV_8U);
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, CV_32F);

    histImage = Scalar(255);
    int binW = cvRound((double)histImage.cols/histSize);
    int x1, y1, x2, y2;
    for(int i = 0; i < histSize; i++)
    {
        x1 = i * binW;
        y1 = histImage.rows;
        x2 = (i + 1) * binW;
        y2 = histImage.rows - cvRound(hist.at<float>(i));
        rectangle(histImage, Point(x1, y1),  Point(x2, y2), Scalar(0), -1);
        
    }
    imshow("histImage", histImage);
    waitKey();
    return 0;
}