#include <iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);

	Mat frame;
	Mat tempMat;
	Mat resultMat;
	Mat refMat;
	Mat dispMat;

	if (!cap.isOpened())
	{
		std::cout << "fail to open video...\n" << std::endl;
		return -1;
	}
	TemplateMatchModes;
	int cnt = 0;

	while (1) {
		cap >> frame;
		if (frame.empty()) break;

		if (cnt == 0) {
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}
		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal, maxVal;
		Point minLoc, maxLoc;
		Point matchLoc;

		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}
		frame.copyTo(dispMat);
		rectangle(dispMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);

		cnt++;
		imshow("template", refMat);
		imshow("dispMat", dispMat);
		waitKey(30);
	}
	return 0;

}
