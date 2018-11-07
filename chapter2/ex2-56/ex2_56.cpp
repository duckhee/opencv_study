#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

template <class T>
T** vec_vec_to_arr_arr(vector< vector<T> > v1)
{
    T** v2 = new T*[v1.size()];
    for(int i = 0; i < v1.size(); i++)
    {
        v2[i] = new T[v1[i].size()];
        for(int j = 0; j < v1[i].size(); j++)
        {
            v2[i][j] = v1[i][j];
        }
    }
    return v2;
}

template <class T>
void delete_arr_arr(T** arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
     
     vector<vector<Point> > contour(2, vector<Point>());
     contour[0].push_back(Point(100, 100));
     contour[0].push_back(Point(200, 100));
     contour[0].push_back(Point(200, 200));
     contour[0].push_back(Point(100, 200));
     contour[1].push_back(Point(300, 200));
     contour[1].push_back(Point(300, 200));
     contour[1].push_back(Point(400, 100));
     contour[1].push_back(Point(400, 200));

     int npts[2] = {contour[0].size(), contour[1].size()};
     int i, j;

     Point *pts1, *pts2;
     pts1 = &contour[0][0];
     pts2 = &contour[1][0];
     Point *P1[] = {pts1, pts2};
     for(i = 0; i < contour.size(); i++)
     {
         for(j = 0; j < contour[i].size(); j++)
         {
             cout<<"P1["<<i<<"] = "<<P1[i]<<endl;
         }
     }

    //polylines(dstImage, (const Point**)&P1, npts, 2, true, Scalar(0, 0, 255));

    pts1 = (Point*)Mat(contour[0]).data;
    pts2 = (Point*)Mat(contour[1]).data;
    Point *P2[2] = {pts1, pts2};
    for(i = 0; i < contour.size(); i++)
    {
        for(j = 0; j < contour[i].size(); j++)
        {
            cout<<"P2["<<i<<"]["<<j<<"] = "<<P2[i][j]<<endl;
        }
    }
    //polylines(dstImage, (const Point**)&P2, npts, 2, true, Scalar(0, 0, 255));

    Point P3[2][4];
    copy(contour[0].begin(), contour[0].end(), P3[0]);
    copy(contour[1].begin(), contour[1].end(), P3[1]);

    for(i = 0; i < contour.size(); i++)
    {
        for(j = 0; j < contour[i].size(); j++)
        {
            cout<<"P3["<<i<<"]["<<j<<"] = "<<P3[i][j]<<endl;
        }
    }

    Point *ptrP3[] = {P3[0], P3[1]};
    //polylines(dstImage, (const Point**)&ptrP3, npts, 2, true, Scalar(0, 0, 255));

    Point **P4 = vec_vec_to_arr_arr<Point>(contour);
    for(i = 0; i < contour.size(); i++)
    {
        for(j = 0; j < contour[i].size(); j++)
        {
            cout<<"P4["<<i<<"]["<<j<<"] = "<<P4[i][j]<<endl;
        }
    }
    polylines(dstImage, (const Point**)P4, npts, 2, true, Scalar(0, 0, 255));
    delete_arr_arr<Point>(P4, contour.size());

    imshow("dstImage", dstImage);
    waitKey();

    return 0;

}