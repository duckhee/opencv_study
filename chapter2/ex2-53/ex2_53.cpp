#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    //vector<int> V1(3, 0);
    //vector< vector<int> > M1(2, V1);
    vector< vector<int> > M1(2, vector<int>(3, 0));

    M1[0][0] = 10;
    M1[0][1] = 20;
    M1[0][2] = 30;
    M1[1][0] = 40;
    M1[1][1] = 50;
    M1[1][2] = 60;

    cout<<"M1.size() = "<<M1.size()<<endl;
    cout<<"M1[0].size() = "<<M1[0].size()<<endl;

    cout<<endl<<"for."<<endl;
    for(int i = 0; i < M1.size(); i++)
    {
        for(int j = 0; j < M1[i].size(); j++)
        {
            cout<<setw(4)<<M1[i][j]<<" ";
        }
        cout<<endl;
    }

    vector< vector<int> >::iterator it1;
    vector<int>::iterator it2;
    cout<<endl<<"iterator."<<endl;
    for(it1 = M1.begin(); it1 != M1.end(); it1++)
    {
        for(it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
        {
            cout<<setw(4)<<*it2<< " ";
        }
        cout<<endl;
    }

    return 0;
}