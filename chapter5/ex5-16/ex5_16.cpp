#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void drawHistogram(Mat &image, Mat hist);

int main()
{
    Mat srcImage1 = imread("ex5_14.jpg", IMREAD_GRAYSCALE);
    if(srcImage1.empty())
    {
        return -1;
    }

    Mat srcImage2 = imread("ex5_15.jpg", IMREAD_GRAYSCALE);
    if(srcImage2.empty())
    {
        return -1;
    }

    int histSize = 256;
    float valueRange[] = {0, 256};
    const float* ranges[] = {valueRange};
    int channels = 0;
    int dims = 1;

    Mat H1;
    calcHist(&srcImage1, 1, &channels, Mat(), H1, dims, &histSize, ranges);
    normalize(H1, H1, 1, 0, NORM_L1, CV_32F);
    //cout<<"H1 = "<<H1<<endl;

    Mat H2;
    calcHist(&srcImage2, 1, &channels, Mat(), H2, dims, &histSize, ranges);
    normalize(H2, H2, 1, 0, NORM_L1, CV_32F);
    //cout<<"H2 = "<<H2<<endl;

    double dist1 = compareHist(H1, H2, HISTCMP_CORREL);
    cout<<"dst1 = "<<dist1<<endl;

    double dist2 = compareHist(H1, H2, HISTCMP_CHISQR);
    cout<<"dist2 = "<<dist2<<endl;

    //CV_COMP_INTERSECT
    double dist3 = compareHist(H1, H2, HISTCMP_INTERSECT);
    cout<<"dist3 = "<<dist3<<endl;
    //CV_COMP_BHATTACHARYYA
    double dist4 = compareHist(H1, H2, HISTCMP_BHATTACHARYYA);
    cout<<"dist4 = "<<dist4<<endl;
 
    Mat histImage1;
    drawHistogram(histImage1, H1);
    imshow("histImage1", histImage1);

    Mat histImage2;
    drawHistogram(histImage2, H2);
    imshow("histImage2", histImage2);   
    waitKey();

    return 0;


}

void drawHistogram(Mat &image, Mat hist)
{
    image.create(512, 512, CV_8U);

    normalize(hist, hist, 0, image.rows, NORM_MINMAX, CV_32F);

    image = Scalar(255);
    int binW = cvRound((double)image.cols/hist.rows);
    int x1, y1, x2, y2;
    for(int i = 0; i < hist.rows; i++)
    {
        x1 = i * binW;
        y1 = image.rows;
        x2 = (i + 1) * binW;
        y2 = image.rows - cvRound(hist.at<float>(i));
        rectangle(image, Point(x1, y1), Point(x2, y2), Scalar(0), -1);
        
    }
}