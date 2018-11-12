#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {6, 7, 9, 8, 2, 1, 4, 3};
    Mat A(2, 4, CV_32F, dataA);
    cout<<"A = "<<A<<endl;

    Mat dst1;
    cv::sort(A, dst1, SORT_EVERY_ROW + SORT_ASCENDING);
    cout<<"dst1 = "<<dst1<<endl;

    Mat dst2;
    sortIdx(A, dst2, SORT_EVERY_ROW + SORT_ASCENDING);
    cout<<"dst2 = "<<dst2<<endl;

    Mat dst3;
    cv::sort(A, dst3, SORT_EVERY_ROW + SORT_DESCENDING);
    cout<<"dst3 = "<<dst3<<endl;

    Mat dst4;
    sortIdx(A, dst4, SORT_EVERY_ROW + SORT_DESCENDING);
    cout<<"dst4 = "<<dst4<<endl;

    Mat dst5;
    cv::sort(A, dst5, SORT_EVERY_COLUMN + SORT_ASCENDING);
    cout<<"dst5 = "<<dst5<<endl;

    Mat dst6;
    sortIdx(A, dst6, SORT_EVERY_COLUMN + SORT_ASCENDING);
    cout<<"dst6 = "<<dst6<<endl;

    Mat dst7;
    cv::sort(A, dst7, SORT_EVERY_COLUMN + SORT_DESCENDING);
    cout<<"dst7 = "<<dst7<<endl;

    Mat dst8;
    sortIdx(A, dst8, SORT_EVERY_COLUMN + SORT_DESCENDING);
    cout<<"dst8 = "<<dst8<<endl;

    return 0;
}