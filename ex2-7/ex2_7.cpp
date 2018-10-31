#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void print(string str,Matx23f& A);

int main()
{
    Matx23f A(1,2,3,4,5,6);
    cout<<"A="<<(Mat)A<<endl;

    Matx13f A0 = A.row(0);
    cout<<"A0="<<(Mat)A0<<endl;

    Matx21f A1 = A.col(0);
    cout<<"A1="<<(Mat)A1<<endl;

    Matx22f A2 = A.get_minor<2,2>(0,1);
    cout<<"A2="<<(Mat)A2<<endl;

    Matx23f B = Matx23f::all(10.0f);
    cout<<"B="<<(Mat)B<<endl;

    Matx23f C, D, E, F;
    C = A+B;
    D = A-B;
    E = A*5;
    F = A.mul(B);

    cout<<"C="<<(Mat)C<<endl;
    cout<<"D="<<(Mat)D<<endl;
    cout<<"E="<<(Mat)E<<endl;
    cout<<"F="<<(Mat)F<<endl;

    float dotAB = A.dot(B);
    cout<<endl<<"dotAB="<<dotAB<<endl;

    Matx22f G = A*B.t();
    cout<<"G="<<(Mat)G<<endl;

}

void print(string str, Matx23f& A)
{
    cout<<str<<"=["<<endl;
    for(int r = 0; r < A.rows;r++)
    {
        for(int c = 0; c < A.cols; c++)
        {
            cout.width(4);
            cout<<A(r,c);
            if(c < A.cols -1)
            {
                cout<<",";
            }
        }
        if(r < A.rows -1)
        {
            cout<<endl;
        }
    }
    cout<<"]"<<endl;
}