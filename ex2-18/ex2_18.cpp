#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

//opencv 2.4.13
/*
template<> inline void Ptr<FILE>::delete_obj()
{
    fclose(obj);
}
*/

//opencv 3.1.0
/*
templat<> void DefaultDeleter<FILE>::operator()(FILE *obj) const
{
    fclose(obj);
}
*/

int main()
{
    CvMat *pA = cvCreateMat(2, 3, CV_32FC1);
    Ptr<CvMat> matA(pA);

}