#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define L 256

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }

    int histSize[] = {L};
    float valueRange[] = {0, L};
    const float* ranges[] = {valueRange};
    int channels[] = {0};
    int dims = 1;

    Mat hist;
    calcHist(&srcImage, 1, channels, Mat(), hist, dims, histSize, ranges, true);
    Mat pdf;
    normalize(hist, pdf, L-1, 0, NORM_L1);

    Mat cdf(pdf.size(), pdf.type());
    cdf.at<float>(0) = pdf.at<float>(0);
    for(int i = 1; i < pdf.rows; i++)
    {
        cdf.at<float>(i) = cdf.at<float>(i -1) + pdf.at<float>(i);
    }

    Mat table(cdf.size(), CV_8U);
    table.at<uchar>(0) = 0;
    for(int i = 1; i < pdf.rows; i++)
    {
        table.at<uchar>(i) = cvRound(cdf.at<float>(i));
    }

    Mat dstImage;
    LUT(srcImage, table, dstImage);

    vector<int>params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(100);
    imwrite("ex5_14.jpg", dstImage, params);

    imshow("dstImage", dstImage);

    waitKey();
    return 0;
}