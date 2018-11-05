#include "opencv2/opencv.hpp"
#include "crtdbg.h" //for window

#ifdef __DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE);
#endif

using namespace cv;
using namespace std;

int main()
{
    _CrtSetDbgFlag(_CRTdBG-ALLOC_MEM_DEF I_CRTDBG_LEAK_CHECK_DF);

    int *ptr = new int[100];
    Ptr<int> intData(ptr);

    for(int i = 0; i < 100; i++)
    {
        intData[i] = i;
    }

    return 0;
}

