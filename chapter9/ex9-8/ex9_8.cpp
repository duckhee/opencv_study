#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../momentTest.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        printf("no image momentTest.jpg\r\n");
        return -1;
    }
    Mat dstImage;
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

    threshold(srcImage, srcImage, 200, 255, THRESH_BINARY);

    int mode = RETR_LIST;
    int method = CHAIN_APPROX_SIMPLE;
    //int method = CHAIN_APPROX_NOME;

    vector<vector<Point> > contours;
    findContours(srcImage, contours, noArray(), mode, method);
    cout<<"contours.size() = "<<contours.size()<<endl;

    for(int k = 0; k < contours.size(); k++)
    {
        Scalar color(rand()&255, rand()&255, rand()&255);
        drawContours(dstImage, contours, k, color, 4);
        cout<<"contours["<<k<<"]'s boundary moments"<<endl;

        Moments M = moments(contours[k]);
        cout<<"spatial moments"<<endl;
        cout<<"M.m00 = "<<M.m00<<endl;
        cout<<"M.m10 = "<<M.m10<<endl;
        cout<<"M.m20 = "<<M.m20<<endl;
        cout<<"M.m30 = "<<M.m30<<endl;

        cout<<"M.m01 = "<<M.m01<<endl;
        cout<<"M.m11 = "<<M.m11<<endl;
        cout<<"M.m21 = "<<M.m21<<endl;
        
        cout<<"M.m02 = "<<M.m02<<endl;
        cout<<"M.m12 = "<<M.m12<<endl;
        cout<<"M.m03 = "<<M.m03<<endl;

        Point2f center;
        center.x = M.m10/M.m00;
        center.y = M.m01/M.m00;
        cout<<"mass center = "<<center<<endl;

        circle(dstImage, center, 5, Scalar(0, 0, 255), -1);
        imshow("dstImage", dstImage);

        cout<<"cneral moments"<<endl;
        cout<<"M.m00 = "<<M.m00<<endl;
        cout<<"M.mu10 = "<<0<<endl;
        cout<<"M.mu20 = "<<M.mu20<<endl;
        cout<<"M.mu30 = "<<M.mu30<<endl;
        
        cout<<"M.mu01 = "<<0<<endl;
        cout<<"M.mu11 = "<<M.mu11<<endl;
        cout<<"M.mu21 = "<<M.mu21<<endl;

        cout<<"M.mu02 = "<<M.mu02<<endl;
        cout<<"M.mu12 = "<<M.mu12<<endl;
        cout<<"M.mu03 = "<<M.mu03<<endl;

        cout<<"central normalized moments"<<endl;

        cout<<"M.nu00 = "<<1<<endl;
        cout<<"M.nu10 = "<<0<<endl;
        cout<<"M.nu20 = "<<M.nu20<<endl;
        cout<<"M.nu30 = "<<M.nu30<<endl;

        cout<<"M.nu01 = "<<0<<endl;
        cout<<"M.nu11 = "<<M.nu11<<endl;
        cout<<"M.nu21 = "<<M.nu21<<endl;
        
        cout<<"M.nu02 = "<<M.nu02<<endl;
        cout<<"M.nu12 = "<<M.nu12<<endl;
        cout<<"M.nu03 = "<<M.nu03<<endl;

        Mat hu;
        HuMoments(M, hu);
        cout<<"Hu's 7 moments = "<<endl;
        for(int i = 0; i < hu.rows; i++)
        {
            cout<<"hu["<<i<<"] = ";
            cout<<hu.at<double>(i)<<endl;
        }

    }

    waitKey();
    return 0;


}