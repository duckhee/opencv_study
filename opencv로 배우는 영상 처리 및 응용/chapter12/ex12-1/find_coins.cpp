#include "preprocess.hpp"

int main()
{
    int coin_no = 20;
    String fname = format("./image/%2d.png", coin_no);
    Mat image = imread(fname, 1);
    /*
    if(image.empty())
    {
        printf("not found image\r\n");
        return -1;
    }
    */
   CV_Assert(image.data);

   Mat th_img = preporcessing(image);
   vector<RotatedRect> circles = find_coins(th_img);

   for(int i = 0; i < circles.size(); i++)
   {
       float radius = circles[i].angle;
       circle(image, circles[i].center, radius, Scalar(0, 255, 0), 2);
   }

   imshow("preprocessing iamge", th_img);
   imshow("coin image", image);
   waitKey();

   return 0;
}