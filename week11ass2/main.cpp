#include <iostream>  
#include <opencv2/opencv.hpp>  

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("D:\\etest.jpg");

	vector<Mat> channels;//定义存储的容器
	split(src, channels);

	Mat dst;
	Mat b = channels[0];//飙泪ue通道的图像
	equalizeHist(b, b);//均衡化

	Mat g = channels[1];
	equalizeHist(g, g);

	Mat r = channels[2];
	equalizeHist(r, r);

	merge(channels, dst);//合并通道

	imshow("src", src);

	imshow("dst", dst);
	waitKey(0);
	return 0;
}
