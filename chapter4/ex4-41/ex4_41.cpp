#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    double dataA[] = {
        2, -1, 1,
        3, 3, 9,
        3, 3, 5
    };
    Mat A(3, 3, CV_64F, dataA);
    cout<<"A = "<<A<<endl;

    Mat B = (Mat_<double>(3, 1) << -1, 0, 4);
    cout<<"B = "<<B<<endl;
    SVD svd(A, SVD::MODIFY_A + SVD::FULL_UV);
    cout<<"svd.u = "<<svd.u<<endl;
    cout<<"svd.w = "<<svd.w<<endl;
    cout<<"svd.vt = "<<svd.vt<<endl;

    Mat X;
    svd.backSubst(B, X);
    cout<<"X = "<<X<<endl;
    
    return 0;
}