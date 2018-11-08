#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage1 = imread("../lena.jpg", -1);
    if(srcImage1.empty())
    {
        printf("no image\r\n");
        return -1;
    }

    cout<<"srcImage1.type() = "<<srcImage1.type()<<endl;
    cout<<"srcImage1.depth() = "<<srcImage1.depth()<<endl;
    cout<<"srcImage1.channels() = "<<srcImage1.channels()<<endl<<endl;

    Mat srcImage2 = imread("../lena.jpg", IMREAD_COLOR);
    if(srcImage2.empty())
    {
        printf("no image\r\n");
        return -1;
    }
    cout<<"srcImage2.type() = "<<srcImage2.type()<<endl;
    cout<<"srcImage2.depth() = "<<srcImage2.depth()<<endl;
    cout<<"srcImage2.channels() = "<<srcImage2.channels()<<endl;

    Mat srcImage3 = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage3.empty())
    {
        printf("no image.\r\n");
        return -1;
    }
    cout<<"srcImage3.type() = "<<srcImage3.type()<<endl;
    cout<<"srcImage3.depth() = "<<srcImage3.depth()<<endl;
    cout<<"srcImage3.channels() = "<<srcImage3.channels()<<endl;

    imwrite("ex3_13.bmp", srcImage1);

    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(100);
    imwrite("ex3_13.jpg", srcImage2, params);

    params.clear();
    params.push_back(IMWRITE_PNG_COMPRESSION);
    params.push_back(9);
    imwrite("ex3_13.png", srcImage3, params);

    imshow("srcImage1", srcImage1);
    imshow("srcImage2", srcImage2);
    imshow("srcImage3", srcImage3);

    waitKey();

    return 0;
}

