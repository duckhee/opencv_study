#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {10, 20, 30, 40, 50, 60};
    float dataB[] = {10, 20, 30, 100, 200, 300};

    Mat A(2, 3, CV_32F, dataA);
    Mat B(2, 3, CV_32F, dataB);
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;

    Mat dst1;
    min(A, B, dst1);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    min(A, 20, dst2);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    max(A, B, dst3);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    max(A, 20, dst4);
    cout<<"dst4 = "<<dst4<<endl;

    return 0;
}