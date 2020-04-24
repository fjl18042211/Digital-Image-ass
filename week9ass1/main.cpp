#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;



float O_Distance(float * a, float* b, int n);
void HOG_ext(Mat & src, int blockSize, int nX, int nY, float * hist);

int main() {
	Mat oriMat = imread("D:\\hogTemplate.jpg", 0);
	Mat test_1 = imread("D:\\img1.jpg", 0);
	Mat test_2 = imread("D:\\img2.jpg", 0);


	int blockSize = 16;
	int nX = oriMat.cols / blockSize;
	int nY = oriMat.rows / blockSize;
	int bins = 9 * nX*nY;

	//开辟内存
	float * ori_hist = new float[bins];
	float * test1_hist = new float[bins];
	float * test2_hist = new float[bins];
	memset(ori_hist, 0, sizeof(float)*bins);
	memset(test1_hist, 0, sizeof(float)*bins);
	memset(test2_hist, 0, sizeof(float)*bins);


	HOG_ext(oriMat, blockSize, nX, nY, ori_hist);
	HOG_ext(test_1, blockSize, nX, nY, test1_hist);
	HOG_ext(test_2, blockSize, nX, nY, test2_hist);


	float O_Dis1 = O_Distance(ori_hist, test1_hist, bins);
	float O_Dis2 = O_Distance(ori_hist, test2_hist, bins);


	cout << "“img1”欧几里得距离为" << (int)O_Dis1 << endl;
	cout << "“img2”欧几里得距离为" << (int)O_Dis2 << endl;
	if (O_Dis1 > O_Dis2)
		cout << "“img2”更接近原图" << endl;
	else
		cout << "“img1”更接近原图" << endl;
	return 0;


}


//HOG特征提取/
void HOG_ext(Mat & src, int blockSize, int nX, int nY, float * hist) {
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	int bias = 0;
	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {

			int bias_PicX = j * blockSize, bias_PicY = i * blockSize;
			for (int k = bias_PicX; k < blockSize + bias_PicX; k++) {
				for (int l = bias_PicY; l < blockSize + bias_PicY; l++) {
					int range = (angle.at<float>(k, l) - 1) / 40;
					*(hist + range + bias) += mag.at<float>(k, l);
				}
			}
			bias += 9;
		}
	}
}


// 欧几里得距离计算
float O_Distance(float * a, float * b, int n) {
	float sum = 0;
	for (int i = 0; i < n; i++) {
		sum += pow(*(a + i) - *(b + i), 2);
	}
	sum = sqrt(sum);

	return sum;
}















