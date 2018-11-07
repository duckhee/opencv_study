#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    vector<Mat> images;

    images.push_back(imread("../desert.jpg"));
    images.push_back(imread("../Hydrangeas.jpg"));
    images.push_back(imread("../Koala.jpg"));
    images.push_back(imread("../Penguins.jpg"));

    for(int i = 0; i < images.size(); ++i)
    {
        imshow("images", images[i]);
        waitKey();
    }

    return 0;

}