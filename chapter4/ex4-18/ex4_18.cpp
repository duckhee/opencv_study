#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {1, 2, 3, 4, 5, 6};
    Mat A(2, 3, CV_32F, dataA);
    cout<<"A = "<<A<<endl;

    Mat dst1;
    reduce(A, dst1, 0, REDUCE_SUM);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    reduce(A, dst2, 1, REDUCE_SUM);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    reduce(A, dst3, 0, REDUCE_AVG);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    reduce(A, dst4, 1, REDUCE_AVG);
    cout<<"dst4 = "<<dst4<<endl;

    Mat dst5;
    reduce(A, dst5, 0, REDUCE_MIN);
    cout<<"dst5 = "<<dst5<<endl;

    Mat dst6;
    reduce(A, dst6, 1, REDUCE_MIN);
    cout<<"dst6 = "<<dst6<<endl;

    Mat dst7;
    reduce(A, dst7, 0, REDUCE_MAX);
    cout<<"dst7 = "<<dst7<<endl;

    Mat dst8;
    reduce(A, dst8, 1, REDUCE_MAX);
    cout<<"dst8 = "<<dst8<<endl;

    return 0;

    
}