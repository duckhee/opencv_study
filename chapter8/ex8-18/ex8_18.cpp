#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define MAX_CLUSTERS  4

void onMouse(int event, int x, int y, int flags, void *param);

vector<Point> g_points;

int main()
{
	Scalar colorTable[MAX_CLUSTERS] = {Scalar(255, 0, 0), Scalar(0, 255, 0), Scalar(100, 100, 255), Scalar(255, 0, 255)};

	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));

	imshow("dstImage", dstImage);
	setMouseCallback("dstImage", onMouse, (void *)&dstImage);

	int K = 2;
	int attempts = 2;
	int flags = KMEANS_RANDOM_CENTERS;
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 1.0);
	bool bEscKey = false;
	int nKey;

	while(!bEscKey)
	{
		nKey = waitKey(0);
		switch(nKey)
		{
			case 27:
				bEscKey = true;
			break;
			case 'r':
				g_points.clear();
				dstImage = Scalar::all(255);
				imshow("dstImage", dstImage);
			break;
			case ' ':
				if(g_points.size() < 1)
				{
					break;
				}
				Mat labels, centers;
				Mat samples(g_points.size(), 1, CV_32FC2);
				for(int i = 0; i < g_points.size(); i++)
				{
					Point pt = g_points[i];
					samples.at<Point2f>(i, 0) = Point2f(pt.x, pt.y);
				}
				kmeans(samples, K, labels, criteria, attempts, flags, centers);

				//display clusters
				for(int i = 0; i < K; i++)
				{
					Point pt = centers.at<Point2f>(i, 0);
					circle(dstImage, pt, 8, colorTable[i], -1);
					circle(dstImage, pt, 10, Scalar(0, 0, 255), 2);
				}
				imshow("dstImage", dstImage);
				break;
		}
	}
	return 0;

}

void onMouse(int event, int x, int y, int flags, void *param)
{
	Mat *data = (Mat *)param;
	Mat dstImage = *data;
	switch(event)
	{
		case EVENT_FLAG_LBUTTON:
			circle(dstImage, Point(x, y), 10, Scalar::all(0), -1);
			g_points.push_back(Point(x, y));
			break;
	}
	imshow("dstImage", dstImage);
}

