#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Mat A(2, 4, CV_64F, dataA);
    cout<<"A = "<<A<<endl;

    Mat dst1 = A.clone();
    randShuffle(dst1);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2 = A.clone();
    randShuffle(dst2, 10);
    cout<<"dst2 = "<<dst2<<endl;

    return 0;
}