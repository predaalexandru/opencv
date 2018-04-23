// test_opencv.cpp : Defines the entry point for the console application.

#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat x(2, 2, CV_32FC1, Scalar(1));
	cv::Mat y(2, 2, CV_32FC1, Scalar(2));

	Mat c(2,2, CV_32FC1);
	c = x * y;

	cout << c;

	getchar();
    return 0;
}

