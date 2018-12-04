#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage = imread("../momentTest.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("no image \r\n");
        return -1;
    }
    Mat dstImage;
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
    threshold(srcImage, srcImage, 200, 255, THRESH_BINARY);

    int mode = RETR_LIST;
    int method = CHAIN_APPROX_SIMPLE;
    //int method = CHAIN_APPROX_NONE;

    vector<vector<Point> > contours;
    findContours(srcImage, contours, noArray(), mode, method);
    cout<<"contours.size() = "<<contours.size()<<endl;

    for(int k = 0; k < contours.size(); k++)
    {
        drawContours(dstImage, contours, k , Scalar(0, 0, 255), 4);
        cout<<"contours["<<k<<"]'s boundary moments"<<endl;

        Moments M = moments(contours[k]);
        Point2f center;
        center.x = M.m10/M.m00;
        center.y = M.m01/M.m00;
        cout<<"mass center = "<<center<<endl;
        circle(dstImage, center, 5, Scalar(0, 0, 255), -1);
        
        Mat hu;
        HuMoments(M, hu);
        cout<<"Hu's 7 moments(contours[k])"<<endl;
        double angle = 45.0;  //rotation, angle = -45.0
        double scale = 0.5;   //scaling, scale = 1.2
        Point t(0, 0); //translation, t(20, 30), (-20, -30)
        cout<<"angle = "<<angle<<endl;
        cout<<"scale = "<<scale<<endl;
        cout<<"translation = "<<t<<endl;

        Mat rot = getRotationMatrix2D(center, angle, scale); //2x3 matrix
        //cout<<"rot.size() = "<<rot.size()<<endl;
        rot.col(2).at<double>(0) += t.x;  //translation
        rot.col(2).at<double>(1) += t.y;

        Mat points(contours[k]);
        transform(points, points, rot);

        vector<Point> contour2;
        points.copyTo(contour2);
        drawContours(dstImage, vector<vector<Point> >(1, contour2), 0, Scalar(0, 255, 0), 4);

        Moments M2 = moments(contour2);
        Point2f center2;
        center2.x = M2.m10/M2.m00;
        center2.y = M2.m01/M2.m00;
        cout<<"mass center2 = "<<center2<<endl;
        circle(dstImage, center2, 5, Scalar(0, 255, 0), -1);
        
        Mat hu2;
        HuMoments(M2, hu2);
        cout<<endl<<"Hu's 7 moments(contour2) = "<<endl;
        for(int i = 0; i < hu2.rows; i++)
        {
            cout<<"hu2["<<i<<"] = ";
            cout<<hu2.at<double>(i)<<endl;
        }
        double distError = norm(hu, hu2); //NORM_L2
        cout<<endl<<"distError = "<<distError<<endl;
        imshow("dstImage", dstImage);
    }
    waitKey();
    return 0;
}