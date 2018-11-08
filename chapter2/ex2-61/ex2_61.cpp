#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat A(1, 3, CV_8U, 100);
    int a = 0;
    int b = 2;
    cout<<"A = "<<A<<endl;
    try{
        //CV_Assert(a != 0);
        if(a == 0)
        {
            //CV_StsDivByZero in OpenCV 2.4.13
            CV_Error(Error::StsDivByZero, "b is zero");
        }
        A /= a;
        cout<<"A1 = "<<A<<endl;

        //CV_Assert(b >= 0 && b < 3);
        if(b < 0 || b > 3)
        {
            //CV_StsOutOfRange in OpenCV 2.4.13
            CV_Error_(Error::StsOutOfRange, ("a = %d is out of range.", b));
        }
        A.at<uchar>(b) = saturate_cast<uchar>(300);
        cout<<"A2 = "<<A<<endl;
        CV_Assert(A.type() == CV_8UC3);
    }catch(cv::Exception& e)
    {
        const char* err_msg = e.what();
        cout<<"Exception("<<e.code<<"):"<<err_msg<<endl;
    }

    return 0;
}