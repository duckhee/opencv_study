#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class ClosePoints
{
	public:
		ClosePoints(int minDist): minDist_(minDist){}

		bool operator()(const Point &p1, const Point &p2) const
		{
			int dist2 = (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
			return dist2 < (minDist_*minDist_);
		}

	private:
		int minDist_;
};

void onMouse(int event, int x, int y, int flags, void *param);
vector<Point> g_points;

int main()
{
	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));

	imshow("dstImage", dstImage);
	setMouseCallback("dstImage", onMouse, (void *)&dstImage);

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
				if(g_points.size()<1)
				{
					break;
				}
				vector<int> labels;
				int K; //#of cluster
				K = partition(g_points, labels, ClosePoints(100));
				cout<<"#of clusters, K = "<<K<<endl;
				//make color tables for displaying objects
				Mat colorTable(K, 1, CV_8UC3);
				Vec3b color;
				for(int k = 0; k < K; k++)
				{
					color[0] = rand()&180+50;
					color[1] = rand()&180+50;
					color[2] = rand()&180+50;
					colorTable.at<Vec3b>(k, 0) = color;
				}
				//display clusters
				for(int i = 0; i < g_points.size(); i++)
				{
					int k = labels[i];
					Point pt = g_points[i];
					color = colorTable.at<Vec3b>(k, 0);
					circle(dstImage, pt, 10, Scalar(color), -1);
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
