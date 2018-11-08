#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    IplImage* image = cvLoadImage("../lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat matA = cvarrToMat(image);
    //Mat matA = cvarrToMat(image).clone();
    

    Mat matB;
    flip(matA, matB, 0);
    imshow("flip image1", matB);

    //CvMat arrB1 = matB;
    //Mat matC1 = cvarrToMat(&arrB1);

    Mat matC;
    flip(matA, matC, 1);
    imshow("flip image2", matC);

    //IplImage arrB2 = matC;
    //Mat matC2 = cvarrToMat(&arrB2);

    waitKey();

    return 0;
}