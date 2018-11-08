#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage(512, 512, CV_8UC3, Scalar::all(255));
    rectangle(srcImage, Point(100, 100), Point(400, 400), Scalar(255, 0, 0), -1);
    //BMP
    vector<uchar> buf1;
    imencode(".bmp", srcImage, buf1);
    Mat dstImage1 = imdecode(buf1, IMREAD_COLOR);
    //Mat dstImage1 = imdecode(buf1, IMREAD_GRAYSCALE);

    imshow("dstImage1", dstImage1);
    ofstream outfile1("test.bmp", ios::binary);
    outfile1.write((const char*)buf1.data(), buf1.size());
    outfile1.close();
    //JPG
    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(90);

    vector<uchar> buf2;
    imencode(".jpg", srcImage, buf2, params);

    Mat dstImage2 = imdecode(buf2, IMREAD_COLOR);
    //Mat dstImage2 = imdecode(buf2, IMREAD_GRAYSCALE);
    imshow("dstImage2", dstImage2);

    ofstream outfile2("test.jpg", ios::binary);
    outfile2.write((const char*)buf2.data(), buf2.size());
    outfile2.close();

    //PNG
    params.clear();
    params.push_back(IMWRITE_PNG_COMPRESSION);
    params.push_back(9);

    vector<uchar> buf3;
    imencode(".png", srcImage, buf3, params);

    Mat dstImage3 = imdecode(buf3, IMREAD_COLOR);
    //Mat dtImaged3 = imdecode(buf3, IMREAD_GRAYSCALE);
    imshow("dstImage3", dstImage3);

    ofstream outfile3("test.png", ios::binary);
    outfile3.write((const char*)buf3.data(), buf3.size());
    outfile3.close();
    waitKey();

    return 0;
}