#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

CV_IMPL void cvPyrSegmentation(IplImage *src, IplImage *dst, CvMemStorage *storage, CvSeq ** comp, int level, double threshold1, double threshold2);
vector<Rect> PyrSegmentation(Mat &src, Mat &dst, int level, int th11, int th2);

int main()
{
	Mat srcImage = imread("../segmentTest.jpg", IMREAD_GRAYSCALE);
	if(srcImage.empty())
	{
		printf("segmentTest not image\r\n");
		return -1;
	}

	int level = 4;
	int th1 = 100;
	int th2 = 30;
	vector<Rect> rects;
	Mat dstImage;
	rects = PyrSegmentation(srcImage, dstImage, level, th1, th2);
	cout<<"rects.size() = "<<rects.size()<<endl;

	Mat dstImageColor;
	cvtColor(dstImage, dstImageColor, COLOR_GRAY2BGR);
	for(int i = 0; i < rects.size(); i++)
	{
		rectangle(dstImageColor, rects[i], Scalar(0, 0, 255), 2);
	}
	imshow("srcImage", srcImage);
	imshow("dstImageColor", dstImageColor);

	waitKey();

	return 0;
}

vector<Rect> PyrSegmentation(Mat &src, Mat &dst, int level, int th1, int th2)
{
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq *components = 0;

	IplImage srcImage = src;
	dst.release();
	dst.create(src.size(), src.type());
	IplImage seqImage = dst;
	cvPyrSegmentation(&srcImage, &seqImage, storage, &components, level, (double)th1, (double)th2);

	vector<Rect> rects;
	CvSeq *first_contour = 0;
	for(int i = 0; i < components->total; i++)
	{
		CvConnectedComp *comp = (CvConnectedComp*)cvGetSeqElem(components, i);
		if(cvRound(comp->value.val[0]) == 0)   //background cluster
		{
			continue;
		}
		Rect r = comp->rect;
		rects.push_back(r);
	}
	cvReleaseMemStorage(&storage);
	return rects;
}


