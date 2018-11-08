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

    Point pt1(10, 10), pt2(400, 400);

    LineIterator it(srcImage, pt1, pt2, 8);

    vector<uchar> buffer(it.count);
    //vector<Vec3b> buf(it.count);
    for(int i = 0; i < it.count; i++, ++it)
    {
        buffer[i] = **it;
        //buffer[i] = srcImage.at<uchar>(it.pos());

        //buffer[i] = *(const Vec3b)*it; //if 8bit channel
        //buffer[i] = srcImage.at<Vec3b>(it.pos()); //if 8bit channel
    }
    cout<<"pixel = "<<(Mat)buffer<<endl;
    line(srcImage, pt1, pt2, Scalar(255), 2);

    //Draw profile using buffer
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
    pt1 = Point(0, dstImage.cols - buffer[0]);

    for(int i = 1; i < buffer.size(); i++, ++it)
    {
        pt2 = Point(i, dstImage.cols - buffer[i]);
        line(dstImage, pt1, pt2, Scalar(255), 2);
        pt1 = pt2;
    }

    imshow("srcImage", srcImage);
    imshow("dstImage", dstImage);
    waitKey();

    return 0;

}