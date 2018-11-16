#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void drawHistogram2D(Mat &image, Mat hist);

int main()
{
    Mat srcImage1(512, 512, CV_8UC2);
    Mat srcImage2(512, 512, CV_8UC2);

    Scalar mean1 = Scalar(128, 128);
    Scalar stddev1 = Scalar(20, 20);
    RNG &rng1 = theRNG();
    rng1.fill(srcImage1, RNG::NORMAL, mean1, stddev1);

    Scalar mean2 = Scalar(110, 128);
    Scalar stddev2 = Scalar(20, 20);
    RNG &rng2 = theRNG();
    rng2.fill(srcImage2, RNG::NORMAL, mean2, stddev2);

    int histSize[] = {32, 32};
    float range1[] = {0, 256};
    float range2[] = {0, 256};
    const float* ranges[] = {range1, range2};
    int channels[] = {0, 1};
    int dims = 2;

    Mat H1;
    calcHist(&srcImage1, 2, channels, Mat(), H1, dims, histSize, ranges);
    normalize(H1, H1, 1, 0, NORM_L1, CV_32F);
    //cout<<"H1 = "<<H1<<endl;
    //cout<<"H1.size() = "<<H1.size()<<endl;

    Mat H2;
    calcHist(&srcImage2, 1, channels, Mat(), H2, dims, histSize, ranges);
    normalize(H2, H2, 1, 0, NORM_L1, CV_32F);
    //cout<<"H2 = "<<H2<<endl;
    //cout<<"H2.size() = "<<H2.size()<<endl;

    int nRows1 = H1.rows * H1.cols;
    Mat S1(nRows1, 3, CV_32F, Scalar(0));
    for(int y = 0; y < H1.rows; y++)
    {
        for(int x = 0; x < H1.cols; x++)
        {
            int n = H1.cols*y + x;
            S1.at<float>(n, 0) = H1.at<float>(y, x);
            S1.at<float>(n, 1) = y;
            S1.at<float>(n, 2) = x;
        }
    }
    cout<<"S1.size() = "<<S1.size()<<endl;

    int nRows2 = H2.rows * H2.cols;
    Mat S2(nRows2, 3, CV_32F, Scalar(0));
    for(int y = 0; y < H2.rows; y++)
    {
        for(int x = 0; x < H2.cols; x++)
        {
            int n = H2.cols * y + x;
            S2.at<float>(n, 0) = H2.at<float>(y, x);
            S2.at<float>(n, 1) = y;
            S2.at<float>(n, 2) = x;
        }
    }
    cout<<"S2.size() = "<<S2.size()<<endl;

    float emdDist = EMD(S1, S2, DIST_L2); //CV_DIST_L2
    cout<<"emdDist = "<<emdDist<<endl;

    float lowerBound = 100;
    float emdDist2 = EMD(S1, S2, DIST_L2, noArray(), &lowerBound);
    cout<<"emdDist2 = "<<emdDist2<<endl;
    cout<<"lowerBound = "<<lowerBound<<endl;

    Mat histImage1;
    drawHistogram2D(histImage1, H1);
    imshow("histImage1", histImage1);

    Mat histImage2;
    drawHistogram2D(histImage2, H2);
    imshow("histImage2", histImage2);

    waitKey();

    return 0;
}

void drawHistogram2D(Mat &image, Mat hist)
{
    if(image.empty())
    {
        image.create(512, 512, CV_8U);
    }
    //image = Scalar(255);

    normalize(hist, hist, 0, 255, NORM_MINMAX, CV_32F);
    int binW = cvRound((double)image.cols/hist.cols);
    int binH = cvRound((double)image.rows/hist.rows);

    int x, y;
    Rect rtROI;
    Mat roi;
    for(int j = 0; j < hist.cols; j++)
    {
        for(int i = 0; i < hist.rows; i++)
        {
            float hValue = hist.at<float>(j, i);
            x = i * binW;
            y = j * binH;
            rtROI = Rect(x, y, binW, binH);
            image(rtROI) = cvRound(hValue);
        }
    }
}