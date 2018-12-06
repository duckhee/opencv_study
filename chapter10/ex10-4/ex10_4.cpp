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
    //Opencv3.1.0
    Ptr<GFTTDetector> goodF = GFTTDetector::create(200, 0.01, 1, 5, true);
    goodF->detect(srcImage, keypoints);
    cout<<"keypoints.size() = "<<keypoints.size()<<endl;

    Mat dstImage(srcImage.size(), CV_8UC3);
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
    //drawKeypoints(srcImage, keypoints, dstImage);

    KeyPoint element;
    for(int k = 0; k < keypoints.size(); k++)
    {
        element = keypoints[k];
        /*
        cout << element.pt << ", " << element.response;
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