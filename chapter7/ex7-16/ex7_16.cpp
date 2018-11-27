#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


int main()
{
    Mat srcImage = imread("alphabet.bmp", IMREAD_GRAYSCALE);
    if(srcImage.empty())
    {
        return -1;
    }
    String tName[] = { "A.bmp", "s.bmp", "b.bmp", "m.bmp" };

    Mat dstImage;
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

    Mat src32f;
    srcImage.convertTo(src32f, CV_32F);
    cout<<"src32f.size()  ="<<src32f.size()<<endl;
    for(int i = 0; i < 4; i++)
    {
        Mat tImage = imread(tName[i], IMREAD_GRAYSCALE);
        if(tImage.empty())
        {
            return -1;
        }
        cout<<"template"<<tName[i]<<endl;
        Mat tmpl32f;
        tImage.convertTo(tmpl32f, CV_32F);
        copyMakeBorder(tmpl32f, tmpl32f, 0, src32f.rows-tmpl32f.rows, 0, src32f.cols-tmpl32f.cols, BORDER_CONSTANT, 0);
        cout<<"tmpl32f.size() = "<<tmpl32f.size()<<endl;

        double phaseCorr;
        //OpenCV 2.4.13
        //Point2d peakLoc = phaseCorrelateRes(src32f, tmpl32f, noArray(), &phaseCorr);

        //OpenCV 3.1.0
        Point2d peakLoc = phaseCorrelate(src32f, tmpl32f, noArray(), &phaseCorr);
        cout<<"phaseCorr = "<<phaseCorr<<endl;
        //Point2d peakLoc = phaseCorrelate(src32f, tmpl32f);
        //cout<<"peakLoc = "<<peakLoc<<endl;

        Point2d center(src32f.cols/2.0, src32f.rows/2.0);
        ///////////////
        //region1//region2//
        /////////////////
        //region3//region4//
        //////////////
        peakLoc = (center-peakLoc); //inverse of peakLoc = (center - t)
        //inverse of fftShift
        if(peakLoc.x < center.x)
        {
            if(peakLoc.y<center.y) // region 1
            {
                peakLoc += center; //to region 4
            }else //region3
            {
                peakLoc.x += center.x; //to region 2
                peakLoc.y -= center.y;
            }
        }
        else
        {
            if(peakLoc.y < center.y) //region 2
            {
                peakLoc.x -= center.x; //to region 3
                peakLoc.y += center.y;
            }
            else //region 4
            {
                peakLoc -= center; //to region 1
            }
        }
        cout<<"peakLoc = "<<peakLoc<<endl;
        		rectangle(dstImage, Point((int)peakLoc.x, (int)peakLoc.y),
			Point(peakLoc.x + tImage.cols, peakLoc.y + tImage.rows), Scalar(255, 0, 0), 2);
    }
    imshow("dstImage", dstImage);
    waitKey();
    return 0;
}