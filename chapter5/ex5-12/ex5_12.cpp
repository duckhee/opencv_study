#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define L 256

int main()
{
    uchar dataA[16] = 
    {
        0, 0, 0, 0, 
        1, 1, 3, 5,
        6, 1, 1, 3,
        4, 3, 1, 7
    };

    Mat A(4, 4, CV_8U, dataA);
    cout<<"A"<<A<<endl;

    int histSize[] = { L };
    float valueRange[] = { 0, L };
    const float* ranges[] = {valueRange};
    int channels[] = { 0 };
    int dims = 1;

    Mat hist;
    calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);
    cout<<"hist = "<<hist<<endl;

    Mat pdf;
    normalize(hist, pdf, L-1, NORM_L1);
    cout<<"pdf = "<<pdf<<endl;
    cout<<"pdf.size() = "<<pdf.size()<<endl;
    cout<<"pdf.type() = "<<pdf.type()<<endl;

    Mat cdf(pdf.size(), pdf.type());
    cdf.at<float>(0) = pdf.at<float>(0);
    for(int i = 0; i < pdf.rows; i++)
    {
        cdf.at<float>(i) = cdf.at<float>(i-1) + pdf.at<float>(i);
    }
    cout<<"cdf = "<<cdf<<endl;

    Mat table(cdf.size(), CV_8U);
    table.at<uchar>(0) = 0;
    for(int i = 1; i < pdf.rows; i++)
    {
        table.at<uchar>(i) = cvRound(cdf.at<float>(i));
    }
    cout<<"table = "<<table<<endl;

    /*
    Mat dst(A.size(), A.type());
    MatConstIterator_<uchar> itDst = dst.begin<uchar>();
    for(; itA != A.end<uchar>(); itA++, itDst++)
    {
        int r = *itA;
        *itDst = table.at<uchar>(r);
    }
    cout<<"dst = "<<dst<<endl;
    */

   return 0;

}