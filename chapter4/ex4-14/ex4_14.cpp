#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    double dataA[] = {0, 0, 1.0, 2.0, 3.0};
    Mat A(1, 4, CV_64F, dataA);
    cout<<"A = "<<A<<endl;

    Mat dst1;
    exp(A, dst1);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    log(A, dst2);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    pow(A, 2.0, dst3);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    sqrt(A, dst4);
    cout<<"dst4 = "<<dst4<<endl;

    return 0;
}