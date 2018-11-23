#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    uchar dataA[] = {
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 9, 9, 1, 1,
        1, 1, 9, 9, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1
    };

    Mat A(6, 6, CV_8U, dataA);
    cout<<"A = "<<A<<endl;

    int ksize = 1; //ksize = 3
    float K[2][9] = {
        {0, 1, 0, 1, -4, 1, 0, 1, 0},
        {2, 0, 2, 0, -8, 0, 2, 0, 2}
    };
    Mat Kernel(3, 3, CV_32F, K[ksize == 3]);

    int ddepth = CV_16S;
    Mat dst1;
    filter2D(A, dst1, ddepth, Kernel);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    Laplacian(A, dst2, ddepth, ksize);
    cout<<"dst2 = "<<dst2<<endl;

    waitKey();

    return 0;
    
}