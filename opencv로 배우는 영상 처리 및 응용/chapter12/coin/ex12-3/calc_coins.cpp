#include "preprocess.hpp"
#include "util.hpp"
#include "classify.hpp"
#include "histogram.hpp"


int main()
{
    int coin_no, hue_bin = 32;
    cout<<" coin number = " ;
    cin>>coin_no;
    String fname = format("../image/%2d.png", coin_no);
    Mat image = imread(fname, 1);
    CV_Assert(image.data);

    Mat th_img = preprocessing(image);
    vector<RotatedRect> circles = find_coins(th_img);
    vector<Mat> coin_img = make_coinImg(image, circles);
    vector<Mat> coin_hist = calc_coin_histo(coin_img, hue_bin);

    int Ncoins[4] = {0};
    vector<int> groups = grouping(coin_hist);
    classify_coins(circles, groups, Ncoins);
    int coin_count = calc_coins(Ncoins);

    String str = format("total coin : %d won", coin_count);
    cout<<str<<endl;
    putText(image, str, Point(10, 50), 1, 2, Scalar(0, 200, 0), 2);

    draw_circle(image, circles, groups);
    imshow("coin picture", image);
    waitKey();

    return 0;
}