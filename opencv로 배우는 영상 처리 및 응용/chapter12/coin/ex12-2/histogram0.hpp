#ifndef __HISTOGRAM0_H__
#define __HISTOGRAM0_H__

//#include "preprocess.hpp"
#include "detect.hpp"


Mat make_palatte(int rows)
{
    Mat hsv(rows, 1, CV_8UC3);
    for(int i = 0; i < rows; i++)
    {
        uchar hue = saturate_cast<uchar>((float)i/rows*180);
        hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);
    }
    cvtColor(hsv, hsv, CV_HSV2BGR);
    return hsv;
}

void draw_hist_hue(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
    Mat hsv_platte = make_palatte(hist.rows);
    
    hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
    float bin = (float)hist_img.cols/hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

    for(int i = 0; i < hist.rows; i++)
    {
        float start_x = (i*bin);
        float end_x = (i+1)*bin;
        Point2f pt1(start_x, 0);
        Point2f pt2(end_x, hist.at<float>(i));

        Scalar color = hsv_platte.at<Vec3b>(i);
        rectangle(hist_img, pt1, pt2, color, -1);
    }
    flip(hist_img, hist_img, 0);
}

void calc_histo(const Mat& image, Mat &hist, Vec3i bins, Vec3f range, int _dims)
{
    int channels[] = {0, 1, 2};
    int histSize[] = {bins[0], bins[1], bins[2]};

    float ranges1[] = {0, range[0]};
    float ranges2[] = {0, range[1]};
    float ranges3[] = {0, range[2]};

    const float *ranges[] = {ranges1, ranges2, ranges3};

    int dims = (_dims <= 0) ? image.channels() : _dims;
    Mat hsv;
    cvtColor(image, hsv, CV_BGR2HSV);
    calcHist(&hsv, 1, channels, Mat(), hist, dims, histSize, ranges);
}

vector<Mat> calc_coin_histo(vector<Mat> coins, int hue_bin)
{
    vector<Mat> histo;
    for(int i = 0; i < (int)coins.size(); i++)
    {
        Mat hist, hist_img;
        calc_histo(coins[i], hist, Vec3i(hue_bin, 0, 0), Vec3f(180, 0, 0), 1);

        hist.at<float>(0) = 0;
        hist.at<float>(1) = 1;
        normalize(hist, hist, 0, 1, NORM_MINMAX);
        histo.push_back(hist);
    }
    return histo;
}




#endif
