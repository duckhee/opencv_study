#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../cornerTest.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("no image cornerTest.jpg\r\n");
        return -1;
    }
    GaussianBlur(srcImage, srcImage, Size(5, 5), 0, 0);

    vector<KeyPoint> keypoints;

    //OpenCv3.1.0
    //FAST(srcImge, keypoints, 10, true);
    Ptr<FastFeatureDetector> fastF = FastFeatureDetector::create(10, false);
    fastF->detect(srcImage, keypoints);
    cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    //
    KeyPointsFilter::removeDuplicated(keypoints);
    cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    //KeyPointsFilter::runByKeypointSize(keypoints, 10);
    //cout<<"Keypoints.size() = "<<keypoints.size()<<endl;

    //KeyPointsFilter::retainBest(keypoints, 10);
    //cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    Mat dstImage(srcImage.size(), CV_8UC3);
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

    KeyPoint element;
    for(int k = 0; k < keypoints.size(); k++)
    {
        element = keypoints[k];
        cout<<element.pt<<", "<<element.response;
        cout<<", "<<element.angle;
        cout<<", "<<element.size;
        cout<<", "<<element.class_id<<endl;
        circle(dstImage, element.pt, cvRound(element.size / 2), Scalar(0, 0, 255), 2);
    }
    //drawKeypoints(srcImage, keypoints, dstImage);
    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}