#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(3, 3, CV_64FC2);

    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j< A.cols; j++)
        {
            A.at<Vec2d>(i, j) = Vec2d(0, i*A.cols + j);
            //A.at<Vec<double, 2>>(i, j) = Vec<double, 2>(0, i * A.cols + j);
        }
    }
    cout<<A<<endl;

    A.create(3, 3, CV_64FC3);
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A.at<Vec3d>(i, j) = Vec3d(0, i*A.cols + j);
            //A.at<Vec<double, 3>>(i, j) = Vec<double, 3>(0, 0, i * A.cols + j);
        }
    }
    cout<<A<<endl;

    A.create(3, 3, CV_64FC4);
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            //A.at<Vec4d>(i, j) = Vec4d(0, 0, 0, i * A.cols + j);
            //A.at<Vec<double, 4>>(i, j) = Vec<double, 4>(0, 0, 0, i * A.cols + j);
            A.at<Scalar>(i, j) = Scalar(0, 0, 0, i * A.cols + j);
        }
    }
    cout<<A<<endl;

    return 0;
}