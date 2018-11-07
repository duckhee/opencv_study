#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    vector<int> V1;
    cout<<"V1 = "<<(Mat)V1<<endl;

    vector<int> V2(3, 0);
    cout<<"V2 = "<<(Mat)V2<<endl;

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> V3(arr, arr+sizeof(arr)/sizeof(arr[0]));
    cout<<"V3 = "<<(Mat)V3<<endl;

    Point pts[] = {Point(100, 100), Point(200, 100), Point(200, 200), Point(100, 200)};
    vector<Point> V4(pts, pts + sizeof(pts)/sizeof(pts[0]));
    cout<<"V4 = "<<V4<<endl;

    vector<Point> V5(V4.begin(), V4.end()); //V5(V4);
    cout<<"V5 = "<<(Mat)V5<<endl;
    return 0;

}