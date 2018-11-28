#include "opencv2/opencv.hpp"

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int threshold_value = 0;

int threshold_type = 3;

int const max_value = 255;

int const max_type = 4;

int const max_BINARY_value = 255;



Mat src, src_g, dst;

char* window_name = "Threshold Demo";



char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";

char* trackbar_value = "Value";



void Threshold_Demo(int, void*);



int main(int argc, char** argv)

{

	/// Load an image

	src = imread("apples.jpg", 1);



	namedWindow("Original image", CV_WINDOW_AUTOSIZE);	//원본 이미지를 나타내기 위한 창을 만든다.

	imshow("Original image", src); // 원본 이미지를 보여줍니다. 



	/// RGB영상을 R채널, G채널, B채널로 분리합니다. 

	Mat image_r(src.rows, src.cols, CV_8UC1);

	Mat image_g(src.rows, src.cols, CV_8UC1);

	Mat image_b(src.rows, src.cols, CV_8UC1);



	Mat out[] = { image_r, image_g, image_b };

	int from_to[] = { 0,2, 1,1, 2,0 };    // BGR 이미지를 RGB로 순서를 바꾸겠다는 의미. 

	mixChannels(&src, 1, out, 3, from_to, 3);



	src_g = image_g;



	namedWindow("G image", CV_WINDOW_AUTOSIZE);	//G 이미지를 나타내기 위한 창을 만든다.

	imshow("G image", src_g); // G 이미지를 보여줍니다. 



	/// Create a window to display results

	namedWindow(window_name, CV_WINDOW_AUTOSIZE);	//결과를 나타내기 위한 창을 만든다.



	/// Create Trackbar to choose type of Threshold

	createTrackbar(trackbar_type,

		window_name, &threshold_type,

		max_type, Threshold_Demo); //Threshold의 타입을 선택하기 위한 트랙바를 만든다.



	createTrackbar(trackbar_value,

		window_name, &threshold_value,

		max_value, Threshold_Demo);



	/// Call the function to initialize

	Threshold_Demo(0, 0); 



	/// Wait until user finishes program

	while (true)

	{

		int c;

		c = waitKey(20);

		if ((char)c == 'e')	// e를 타이핑하면 프로그램 종료. 

		{

			break;

		}

	}

}





void Threshold_Demo(int, void*)

{

	/* 0: Binary

	1: Binary Inverted

	2: Threshold Truncated

	3: Threshold to Zero

	4: Threshold to Zero Inverted

	*/



	threshold(src_g, dst, threshold_value, max_BINARY_value, threshold_type); // Threshold operation 함수 실행



	imshow(window_name, dst);

}