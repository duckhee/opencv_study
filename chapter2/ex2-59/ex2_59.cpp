#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    FileStorage fs("ex2_59.xml", FileStorage::READ);
    //FileStorage fs("ex2_59.yml", FileStorage::READ);
    //FileStorage fs("ex2_50.yaml", FileStorage::READ);

    if(!fs.isOpened())
    {
        cerr<<"The file is not oppend! FAIL"<<endl;
        return 1;
    }
    string date;
    fs["Date"]>>date;
    cout<<"Date."<<date<<endl;

    string sName;
    fs["Name"]>>sName;
    cout<<"name."<<sName<<endl;

    int nAge;
    fs["age"]>>nAge;
    cout<<"age."<<nAge<<endl;

    float fAngle;
    fs["angle"]>>fAngle;
    cout<<"angle."<<fAngle<<endl;

    double dScale;
    fs["scale"]>>dScale;
    cout<<"scale."<<dScale<<endl;

    Point ptCenter;
    fs["center"]>>ptCenter;
    cout<<"center."<<ptCenter<<endl;

    FileNode node = fs["Images"];
    if(node.type() != FileNode::SEQ)
    {
        cerr<<"It is not a sequence! FAIL"<<endl;
        return 1;
    }

    cout<<"node[0]:"<<(string)node[0]<<endl;
    cout<<"node[1]:"<<(string)node[1]<<endl;
    cout<<"node[2]:"<<(string)node[2]<<endl;
    
    cout<<node.name()<<"=[";
    FileNodeIterator it;
    for(it = node.begin(); it != node.end(); it++)
    {
        cout<<(string)*it<<", ";
    }
    cout<<"]"<<endl<<endl;

    node = fs["Box"];
    if(node.type() != FileNode::MAP)
    {
        cerr<<"It is not a mapping! FAIL"<<endl;
        return 1;
    }
    cout<<node.name()<<"={";
    cout<<"Left : "<<(int)(node["Left"])<<", ";
    cout<<"Top : "<<(int)(node["Top"])<<", ";
    cout<<"Right : "<<(int)(node["Right"])<<", ";
    cout<<"Bottom : "<<(int)(node["Bottom"])<<"}"<<endl<<endl;

    vector<int> V1;
    fs["V1"]>>V1;
    cout<<fs["V1"].name()<<"."<<(Mat)V1<<endl<<endl;
    Mat matB;
    fs["matB"]>>matB;
    cout<<fs["matB"].name()<<"."<<matB<<endl<<endl;
    fs.release();
    return 0;
}