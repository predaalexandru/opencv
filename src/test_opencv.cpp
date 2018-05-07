// test_opencv.cpp : Defines the entry point for the console application.

#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat x(100, 100, CV_8UC3, Scalar(255, 0, 225));

	cv::Mat a(2, 2, CV_8UC1, Scalar(65));

	unsigned char k = 66;
	a.at<unsigned char>(0, 0) = k;

	unsigned char *y = a.ptr<unsigned char>(0);

	//cout << y[1];

	cv::Mat b(2, 2, CV_8UC3, Scalar(65, 255, 0));
	//cout << b;
	Vec3b c = b.at<Vec3b>(0, 0);

	//cout << c;

	Vec3b d;
	d[0] = 5;
	d[1] = 3;
	d[2] = 6;

	b.at<Vec3b>(0, 0) = d;
	cout << b;

	//cout << k;
	//cout << a;

	//cvNamedWindow("Prima");
	//imshow("Prima", x);

	//waitKey(0);

    //return 0;

	getchar();
}

