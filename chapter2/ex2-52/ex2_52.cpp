#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    vector<float> V1;
    V1.push_back(10.0f);
    V1.push_back(20.0f);
    V1.push_back(30.0f);
    V1.push_back(40.0f);

    cout<<"V1.capacity() = "<<V1.capacity()<<endl;
    cout<<"V1.size() = "<<V1.size()<<endl;

    cout<<"for."<<endl;
    for(int i = 0; i < V1.size(); i++)
    {
        cout<<V1[i]<<endl;
    }
    V1.erase(V1.begin() + 2);

    cout<<endl<<"it1 : "<<endl;
    vector<float>::iterator it1;
    for(it1 = V1.begin(); it1 != V1.end(); it1++)
    {
        cout<<*it1<<endl;
    }

    cout<<endl<<"reverse_iterator."<<endl;

    V1.insert(V1.begin() + 2, 30.0f);

    vector<float>::reverse_iterator it2;
    for(it2 = V1.rbegin(); it2 != V1.rend(); it2++)
    {
        cout<<*it2<<endl;
    }

    V1.clear();
    cout<<"V1.capacity() = "<<V1.capacity()<<endl;
    cout<<"V1.size() = "<<V1.size()<<endl;

    return 0;
}