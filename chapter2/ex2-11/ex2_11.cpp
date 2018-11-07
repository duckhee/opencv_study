#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Matx33d A(2, -1, 1, 3, 3, 9, 3, 3, 5);
    Matx31d b(-1, 0, 4);
    
    Matx31d X = A.solve(b);

    cout<<"X="<<(Mat)X<<endl;

    Mat X2;
    solve((Mat)A, (Mat)b, X2);
    cout<<"X2="<<(Mat)X2<<endl;

    return 0;
}