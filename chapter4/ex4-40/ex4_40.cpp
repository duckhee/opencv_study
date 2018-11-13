#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    double dataA[] = {
        1, 0, 0, 0, 2, 
        0, 0, 3, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 4, 0, 0, 0
    };
    Mat A(4, 5, CV_64F, dataA);
    cout<<"A = "<<A<<endl;
    Mat A1 = A.clone();
    SVD svd(A1, SVD::MODIFY_A + SVD::FULL_UV);
    cout<<"svd.u = "<<svd.u<<endl;
    cout<<"svd.w = "<<svd.w<<endl;
    cout<<"svd.vt = "<<svd.vt<<endl;

    Mat W = Mat::zeros(A.size(), A.type());
    for(int i = 0; i < svd.w.rows; i++)
    {
        W.at<double>(i, i) = svd.w.at<double>(i, 0);
    }
    cout<<"W = "<<W<<endl;
    //cout<<"svd.u.size() = "<<svd.u.size()<<endl;
    //cout<<"W.size() = "<<W.size()<<endl;
    //cout<<"svd.vt.size() = "<<svd.vt.size()<<endl;

    Mat A2 = svd.u * W * svd.vt;
    cout<<"A2 = "<<A2<<endl;

    return 0;

}