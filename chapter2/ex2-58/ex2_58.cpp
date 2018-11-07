#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    FileStorage fs("ex2_58.xml", FileStorage::WRITE);
    //FileStorage fs("ex2_58.yml", FileStorage::WRITE);
    //FileStorage fs("ex2_58.yaml", FileStorage::WRITE);
    
    time_t date;
    time(&date);
    fs<<"Date"<<asctime(localtime(&date));

    fs<<"name"<<"KDK";
    fs<<"age"<<25;

    fs<<"Images"<<"["; //Images - Sequence
    fs<<"Apple.jpg"<<"Banana.jpg"<<"Orange.jpg";
    fs<<"]";

    fs<<"Box";
    fs<<"{"<<"Left"<<100;
    fs<<"Top"<<200;
    fs<<"Right"<<300;
    fs<<"Bottom"<<400<<"}";

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> V1(arr, arr+sizeof(arr)/sizeof(arr[0]));
    fs<<"V1"<<V1;

    Point2f ptCenter(256.0f, 256.0f);
    float angle = 45;

    double scale = 10.0;
    fs<<"angle"<<angle;
    fs<<"scale"<<scale;
    fs<<"center"<<ptCenter;

    Mat matR = getRotationMatrix2D(ptCenter, angle, scale);
    fs<<"matR"<<matR;
    fs.release();

    return 0;

}