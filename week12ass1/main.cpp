#include <iostream>  
#include <opencv2/opencv.hpp>  

using namespace cv;
using namespace std;
int main() {
	VideoCapture cap;//实例化一个videocapture类，名称为cap
	cap.open(0);//
	if (!cap.isOpened())
	{
		std::cout << "不可打开视频文件" << std::endl;
		return -1;
	}
	int cnt = 0;
	Mat frame, bgMat, bny_subMat, subMat;
	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0)
		{
			frame.copyTo(bgMat);
		}
		else
		{
			absdiff(frame, bgMat, subMat);
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);
			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
		cnt++;
	}
	return 0;


}