#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	const int MAX_CLUSTERS = 5;
	Vec3b colorTab[] =
	{
		Vec3b(0, 0, 255),
		Vec3b(0, 255, 0),
		Vec3b(255, 100, 100),
		Vec3b(255, 0, 255),
		Vec3b(0, 255, 255)
	};
	Mat data, labels;
	Mat src = imread("D:\\2.jpg");
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
		{
			Vec3b point = src.at<Vec3b>(i, j);
			Mat tmp = (Mat_<float>(1, 3) << point[0], point[1], point[2]);
			data.push_back(tmp);
		}

	//根据浏览图片，确定k=2
	kmeans(data, 2, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
		3, KMEANS_RANDOM_CENTERS);

	int n = 0;
	//显示聚类结果，不同的类别用不同的颜色显示
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
		{
			int clusterIdx = labels.at<int>(n);
			src.at<Vec3b>(i, j) = colorTab[clusterIdx];
			n++;
		}
	imshow("src", src);
	waitKey(0);

	return 0;
}



