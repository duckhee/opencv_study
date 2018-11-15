#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg");
    if(srcImage.empty())
    {
        return -1;
    }
    int histSize[] = {64, 64};
    float range1[] = {0, 256};
    float range2[] = {0, 256};

    const float* ranges[] = {range1, range2};
    const int channels[] = {0, 1};
    int dims = 2;

    Mat hist;
    calcHist(&srcImage, 1, channels, Mat(), hist, dims, histSize, ranges);
    cout<<"hist.size() = "<<hist.size()<<endl;
    normalize(hist, hist, 0, 255, NORM_MINMAX, CV_32F);

    Mat histImage(512, 512, CV_8U, Scalar(255));
    int binW = cvRound((double)histImage.cols/histSize[1]);
    int binH = cvRound((double)histImage.rows/histSize[0]);

    int x, y;
    Rect rtROI;
    Mat roi;
    for(int i = 0; i < histSize[1]; i++)
    {
        for(int j = 0; j < histSize[0]; j++)
        {
            float hValue = hist.at<float>(j, i);
            x = i * binW;
            y = j * binH;
            rtROI = Rect(x, y, binW, binH);
            histImage(rtROI) = hValue;
        }
    }
    imshow("histImage", histImage);
    waitKey();
    return 0;


}