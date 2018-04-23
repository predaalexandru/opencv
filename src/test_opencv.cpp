// test_opencv.cpp : Defines the entry point for the console application.

#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat x(100, 100, CV_8UC3, Scalar(255, 0, 225));

	cvNamedWindow("Prima");
	imshow("Prima", x);


	waitKey(0);

    return 0;
}

