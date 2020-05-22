#include <iostream>  
#include <opencv2/opencv.hpp>  

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("D:\\etest.jpg");

	vector<Mat> channels;//����洢������
	split(src, channels);

	Mat dst;
	Mat b = channels[0];//���ueͨ����ͼ��
	equalizeHist(b, b);//���⻯

	Mat g = channels[1];
	equalizeHist(g, g);

	Mat r = channels[2];
	equalizeHist(r, r);

	merge(channels, dst);//�ϲ�ͨ��

	imshow("src", src);

	imshow("dst", dst);
	waitKey(0);
	return 0;
}
