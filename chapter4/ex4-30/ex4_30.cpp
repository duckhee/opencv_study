#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    float dataA[] = {1, 0, -1, 0, 1, 0, -1, 0, 1};

    Mat A(3, 3, CV_32F, dataA);
    cout<<"A = "<<A<<endl;

    Mat eigenvalues;
    eigen(A, eigenvalues);
    cout<<"eigenvalues = "<<eigenvalues<<endl;

    Mat eigenvectors;
    eigen(A, eigenvalues, eigenvectors);
    cout<<"eignevalues = "<<eigenvalues<<endl;
    cout<<"eigenvectors = "<<eigenvectors<<endl;

    return 0;
}