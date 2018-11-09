#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    double dataX[] = {0.0, 10.0, 10.0, 0.0};
    double dataY[] = {0.0, 0.0, 10.0, 10.0};

    Mat X(1, 4, CV_64F, dataX);
    Mat Y(1, 4, CV_64F, dataY);
    cout<<"X = "<<X<<endl;
    cout<<"Y = "<<Y<<endl;

    Mat mag;
    magnitude(X, Y, mag);
    cout<<"mag = "<<mag<<endl;

    Mat angle1;
    phase(X, Y, angle1);
    cout<<"angle1 = "<<angle1<<endl;

    Mat angle2;
    phase(X, Y, angle2, true);
    cout<<"angle2 = "<<angle2<<endl;

    Mat mag3, angle3;
    cartToPolar(X, Y, mag3, angle3);
    cout<<"mag3 = "<<mag3<<endl;
    cout<<"angle3 = "<<angle3<<endl;

    Mat X3, Y3;
    polarToCart(mag3, angle3, X3, Y3);
    cout<<"X3 = "<<X3<<endl;
    cout<<"Y = "<<Y3<<endl;

    return 0;
}