#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage = imread("../CornerTest.jpg", IMREAD_GRAYSCALE);
    //Mat srcImage = imread("../book.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("no image \r\n");
        return -1;
    }
    GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

    vector<KeyPoint> keypoints;
    Mat descriptors;

    //OpenCV 3.1.0
    Ptr<ORB> orbF = ORB::create();
    //orbF->detectAndCompute(srcImage, noArray(), keypoints, descriptors);
    //cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    orbF->detect(srcImage, keypoints);
    KeyPointsFilter::removeDuplicated(keypoints);
    KeyPointsFilter::retainBest(keypoints, 10);
    cout<<"keypoints.size() = "<<keypoints.size()<<endl;
    orbF->compute(srcImage, keypoints, descriptors);

    FileStorage fs("Keypoints.yml", FileStorage::WRITE);
    write(fs, "keypoints", keypoints);
    write(fs, "descriptors", descriptors);
    fs.release();

    Mat dstImage(srcImage.size(), CV_8UC3);
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
    drawKeypoints(srcImage, keypoints, dstImage);

    KeyPoint element;
    for(int k = 0; k < keypoints.size(); k++)
    {
        element = keypoints[k];
        RotatedRect rRect = RotatedRect(element.pt, Size2f(element.size, element.size), element.angle);
        Point2f vertices[4];
        rRect.points(vertices);
        for(int i = 0; i < 4; i++)
        {
            line(dstImage, vertices[i], vertices[(i+1)%4], Scalar(0, 255, 0), 2);
        }
        circle(dstImage, element.pt, cvRound(element.size / 2), Scalar(rand()%256, rand()%256, rand()%256), 2);
    }
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}