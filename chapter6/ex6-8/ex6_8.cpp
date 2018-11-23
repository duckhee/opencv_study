#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    uchar dataA[] = {
        1, 2, 4, 5, 2, 1,
        3, 6, 6 ,9, 0, 3,
        1, 8, 3, 7, 2, 5,
        2, 9, 8, 9, 9, 1,
        3, 9, 8, 8, 7, 2,
        4, 9, 9, 9, 9, 3
    };

    Mat A(6, 6, CV_8U, dataA);
    cout<<"A = "<<A<<endl;

    int border = 1;
    Mat B;
    copyMakeBorder(A, B, border, border, border, border, BORDER_REPLICATE);
    cout<<"B = "<<B<<endl;

    int ksize = border * 2 + 1; //ksize = 3 if border = 1
    Mat dst1;
    medianBlur(A, dst1, ksize);
    cout<<"dst1 = "<<dst1<<endl;
    
    Mat dst2;
    blur(A, dst2, Size(ksize, ksize));
    cout<<"dst2 = "<<dst2<<endl;

    waitKey();

    return 0;

}