#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Size size1(320, 240), size2(640, 480);
    Size size3 = size1 * 2;
    Size size4 = size1 + size2;
    Size size5 = Size(800, 600);

    cout<<"size1:"<<size1<<endl;
    cout<<"size1.area():"<<size1.area()<<endl;
    cout<<"size2:"<<size2<<endl;
    cout<<"size3:"<<size3<<endl;
    cout<<"size4:"<<size4<<endl;
    cout<<"size5:"<<size5<<endl;

    if(size2 == size3)
    {
        cout<<"size2 and size3 are the same size"<<endl;
    }

    return 0;
}