#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg");
    if(srcImage.empty())
    {
        return -1;
    }
    cout<<"srcImage.type() = "<<srcImage.type()<<endl;
    vector<Mat> bgrPlanes;
    split(srcImage, bgrPlanes);
    imshow("bgrPlanes[0]", bgrPlanes[0]);
    imshow("bgrPlanes[1]", bgrPlanes[1]);
    imshow("bgrPlanes[2]", bgrPlanes[2]);

    Mat X = srcImage.reshape(1, srcImage.rows * srcImage.cols); 
    cout<<"X.size()"<<X.size()<<endl;
    //CV_PCA_DATA_AS_ROW in OpenCV 2.4.13
    PCA pca(X, noArray(), 0);

    Mat Y;
    pca.project(X, Y);
    cout<<"Y.size() = "<<Y.size()<<endl;

    Mat Y2 = Y.reshape(3, srcImage.rows);
    cout<<"Y2.size() = "<<Y2.size()<<endl;
    
    vector<Mat> yPlanes;
    split(Y2, yPlanes);
    cout<<"yPlanes[0].type() = "<<yPlanes[0].type()<<endl;;

    yPlanes[0].convertTo(yPlanes[0], CV_8U);
    yPlanes[1].convertTo(yPlanes[1], CV_8U);
    yPlanes[2].convertTo(yPlanes[2], CV_8U);
    cout<<"yPlanes[0].type() = "<<yPlanes[0].type()<<endl;
    //yPlanes[0] *= 1.0/255.0;
    //yPlanes[1] *= 1.0/255.0;
    //yPlanes[2] *= 1.0/255/0;

    imshow("yPlanes[0]", yPlanes[0]);
    imshow("yPlanes[1]", yPlanes[1]);
    imshow("yPlanes[2]", yPlanes[2]);
    //imshow("srcImage", srcImage);
    waitKey();

    return 0;
}