#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    int sizes[] = {2, 3, 4};
    Mat A(3, sizes, CV_32FC1);
    Mat B(3, sizes, CV_32FC1, Scalar(0));
    cout<<"B.dims = "<<B.dims<<endl;
    cout<<"B.rows = "<<B.rows<<endl;
    cout<<"B.cols = "<<B.cols<<endl;

    cout<<"B.size[0] = "<<B.size[0]<<endl;
    cout<<"B.size[1] = "<<B.size[1]<<endl;
    cout<<"B.size[2] = "<<B.size[2]<<endl;

    for(int i = 0; i < B.size[0]; i++)
    {
        cout<<"\rB["<<i<<"]"<<endl;
        for(int j = 0; j < B.size[1]; j++)
        {
            for(int k = 0; k < B.size[2]; k++)
            {
                cout<<B.at<float>(i, j, k);
                if(k != B.size[2] - 1)
                {
                    cout<<", ";
                }else
                {
                    cout<<", ";
                }
            }
            cout<<endl;
        }
    }

    return 0;
}