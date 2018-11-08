#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../lena.jpg", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }

    namedWindow("srcImage");
    imshow("srcImage", srcImage);
    int x = 100;
    int y = 100;    
    moveWindow("srcImage", x, y);

    int nKey;
    while(1)
    {
        nKey = waitKey(0);
        //printf("%x\n", nKey);
        if(nKey == 0x1B)
        {
            break;
        }
        switch(nKey)
        {
            case 0x250000:
                x -= 10;
            break;
            case 0x270000:
                x += 10;
            break;
            case 0x260000:
                y -= 10;
            break;
            case 0x280000:
                y += 10;
            break;
        }
        moveWindow("srcImage", x, y);
    }

    return 0;
    
}