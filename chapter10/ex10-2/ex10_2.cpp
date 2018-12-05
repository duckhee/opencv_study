#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage = imread("shapes.jpg", IMREAD_GRAYSCALE); 
    //  Mat srcImage = imread("pattern.jpg", IMREEAD_GRAYSCALE);
    //	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
    //	Mat srcImage = imread("book.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("no image \r\n");
        return -1;
    }
    GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

    vector<vector<Point> > msers;
    //Opencv3.1.0
    Ptr<MSER> mserF = MSER::create(10);  //5, 10, 20
    vector<Rect> bboxes;
    mserF->detectRegions(srcImage, msers, bboxes);
    cout<<"msers.size() = "<<msers.size()<<endl;
    cout<<"bboxes.size() = "<<bboxes.size()<<endl;

    vector<KeyPoint> keypoints;  //center points in bboxes
    mserF->detect(srcImage, keypoints);
    cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    Mat dstImage(srcImage.size(), CV_8UC3);
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
    drawKeypoints(srcImage, keypoints, dstImage);

    for(int k = 0; k < msers.size(); k++)
    {
        // rectangle(dstImage, Point(bboxes[k].x, bboxes[k].y), Point(bboxes[k].x+bboxes[k].width, bboxes[k].y+bboxes[k].height), Scalar(255, 0, 0), 1);
        RotatedRect box = fitEllipse(msers[k]);
        ellipse(dstImage, box, Scalar(rand()%256, rand()%256, rand()%256), 2);
    }
    imshow("dstImage", dstImage);

    waitKey();

    return 0;

}