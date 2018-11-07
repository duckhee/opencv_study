#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

template <class T>
T* vec_to_arr(vector<T> v1) //1D array
{
    T* v2 = new T[v1.size()];
    for(int i = 0; i < v1.size(); i++)
    {
        v2[i] = v1[i];
    }
    return v2;
}

template<class T>
void delete_arr(T* arr)
{
    delete[] arr;
}

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

    vector<Point> contour;
    contour.push_back(Point(100, 100));
    contour.push_back(Point(200, 100));
    contour.push_back(Point(200, 200));
    contour.push_back(Point(100, 200));

    int npts[] = {contour.size()};
    int i;

    Point *P1 = &contour[0];
    for(i = 0; i < contour.size(); i++)
    {
        cout<<"P1["<<i<<"] = "<<P1[i]<<endl;
    }
    //polylines(dstImage, (const Point**)&P1, npts, 1, true, Scalar(0, 0, 255));

    Point *P2 = (Point *)Mat(contour).data;
    for(i = 0; i < contour.size(); i++)
    {
        cout<<"P2["<<i<<"] = "<<P2[i]<<endl;
    }
    //polylines(dstImage, (const Point**)&P2, npts, 1, true, Scalar(0, 0, 255));

    Point P3[4];
    copy(contour.begin(), contour.end(), P3);
    for(i = 0; i < contour.size(); i++)
    {
        cout<<"P3["<<i<<"] = "<<P3[i]<<endl;
    }

    //Point *ptrP3 = P3;
    //polylines(dstImage, (const Point**)&P3, npts, 1, true, Scalar(0, 0, 255));

    Point *P4 = vec_to_arr<Point>(contour);

    for(i = 0; i < contour.size(); i++)
    {
        cout<<"P4["<<i<<"] = "<<P4[i]<<endl;
    }
    polylines(dstImage, (const Point**)&P4, npts, 1, true, Scalar(0, 0, 255));
    delete_arr<Point>(P4);

    imshow("dstImage", dstImage);
    waitKey();

    return 0;
}