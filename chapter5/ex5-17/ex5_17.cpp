#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    //http://ai.sanford.edu/~rubner/emd/example1.c
    float dataP[] = {
        0.4, 100, 40, 22, 
        0.3, 211, 20, 2,
        0.2, 32, 190, 150,
        0.1, 2, 100, 100
    };
    float dataQ[] = {
        0.5, 0, 0, 0, 
        0.3, 50, 100, 80,
        0.2,255, 255, 255
    };

    Mat S1(4, 4, CV_32F, dataP);
    Mat S2(3, 4, CV_32F, dataQ);
    cout<<"S1 = "<<S1<<endl;
    cout<<"S2 = "<<S2<<endl;

    float emdDist = EMD(S1, S2, DIST_L2);
    cout<<"emdDist = "<<emdDist<<endl;

    //lowerBound and EMD
    Mat flow2;
    float lowerBound = 100;
    float emdDist2 = EMD(S1, S2, DIST_L2, noArray(), &lowerBound, flow2);
    cout<<"emdDist2 = "<<emdDist2<<endl;
    cout<<"lowerBound = "<<lowerBound<<endl;
    cout<<"flow2 = "<<flow2<<endl;

    //DIST_USER
    Mat cost(4, 3, CV_32F, Scalar(0));
    float x1, y1, z1;
    float x2, y2, z2;
    float dx, dy, dz;
    double dist;
    double maxValue;

    for(int i = 0; i < S1.rows; i++)
    {
        x1 = S1.at<float>(i, 1);
        y1 = S1.at<float>(i, 2);
        z1 = S1.at<float>(i, 3);
        for(int j = 0; j < S2.rows; j++)
        {
            x2 = S2.at<float>(j, 1);
            y2 = S2.at<float>(j, 2);
            z2 = S2.at<float>(j, 3);
            dx = (x1 - x2);
            dy = (y1 - y2);
            dz = (z1 - z2);
            cost.at<float>(i, j) = sqrt(dx*dx + dy*dy + dz*dz); //DIST_L2
            cost.at<float>(i, j) = abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2);

            //maxValue = (abs(x1-x2)>abs(y1-y2))? abs(x1-x2):abs(y1-y2);
            //maxValue = (abs(x1-x2)>maxValue)?abs(z1-z2):maxValue;
            //cost.at<float>(i, j) = maxValue; //DIST_C
        }   
    }

    cout<<"cost = "<<cost<<endl;

    Mat SS1 = S1.col(0).clone();
    Mat SS2 = S2.col(0).clone();
    cout<<"SS1 = "<<SS1<<endl;
    cout<<"SS2 = "<<SS2<<endl;

    Mat flow3;
    float emdDist3 = EMD(SS1, SS2, DIST_USER, cost, 0, flow3);
    cout<<"emdDist3 = "<<emdDist3<<endl;
    cout<<"flow3 = "<<flow3<<endl;

    return 0;
    

}