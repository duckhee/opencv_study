#ifndef __PREPROCESS_H__
#define __PREPROCESS_H__


#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Mat preporcessing(Mat img){ //전처리 함수
    Mat gray, th_img;
    cvtColor(img, gray, CV_BGR2GRAY); //명암도 변환
    GaussianBlur(gray, gray, Size(7, 7), 2, 2); //블러링

    threshold(gray, th_img, 130, 255, THRESH_BINARY | THRESH_OTSU); //이진화
    morphologyEx(th_img, th_img, MORPH_OPEN, Mat(), Point(-1, -1), 1); //열림연산

    return th_img;

}

vector<RotatedRect> find_coins(Mat img){  //전처리 함수
    vector<vector<Point> > contours;
    //외곽선 검출
    findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<RotatedRect> circles;
    for(int i = 0; i < (int)contours.size(); i++)
    {
        RotatedRect mr = minAreaRect(contours[i]); //외곽선의 최소 영역 사각형
        mr.angle = (mr.size.width + mr.size.height)/4.0f;  //빈자름을 각도에 저장

        if(mr.angle > 18)
        {
            circles.push_back(mr);
        }
    }

    return circles;
}

#endif
