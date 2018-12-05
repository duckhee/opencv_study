#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage = imread("../shapes.jpg", IMREAD_GRAYSCALE);
//	Mat srcImage = imread("pattern.jpg", IMREAD_GRAYSCALE);
//	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
//	Mat srcImage = imread("book.jpg", IMREAD_GRAYSCALE);    
    if(srcImage.empty())
    {
        printf("no image \r\n");
        return -1;
    }
    GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

    vector<KeyPoint> keypoints;

    SimpleBlobDetector::Params params = SimpleBlobDetector::Params();
    params.blobColor = 0;
    params.thresholdStep = 5;
    params.minThreshold = 20;
    params.maxThreshold = 100;
    params.minDistBetweenBlobs = 5;

    params.filterByColor = true;
//    params.filterByColor = false;
    params.filterByArea = false;
    params.filterByInertia = false;
    params.filterByCircularity = false;
    params.filterByConvexity = false;

    //Opencv3.1.0
    Ptr<SimpleBlobDetector> blobF = SimpleBlobDetector::create(params);
    blobF->detect(srcImage, keypoints);
    cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    //draw keypoints
    Mat dstImage(srcImage.size(), CV_8UC3);
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
    drawKeypoints(srcImage, keypoints, dstImage);

    //filtering key points
    KeyPointsFilter::removeDuplicated(keypoints);
    //cout<<:keypoints.size() = "<<keypoints.size()<<endl;

    KeyPointsFilter::runByKeypointSize(keypoints, 10);
    //cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    KeyPointsFilter::retainBest(keypoints, 50);
    cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    KeyPoint element;
    for(int k = 0; k < keypoints.size(); k++)
    {
        element = keypoints[k];
        /*
        cout << element.pt << ", " << element.response ;
		cout << ", " << element.angle  ;
		cout << ", " << element.size  ;
		cout << ", " << element.class_id << endl;
        */
       circle(dstImage, element.pt, cvRound(element.size / 2), Scalar(0, 0, 255), 2);
    }
    imshow("dstImage", dstImage);

    waitKey();

    return 0;

}