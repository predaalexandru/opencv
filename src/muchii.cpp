#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cam;
	if (!cam.open(0)) {
		cout << "Nu am putut deschide camera!" << endl;
		getchar();
		return 0;
	}

	Mat imagine;
	cvNamedWindow("Prima");

	while (1) {
		cam >> imagine;
		cvtColor(imagine, imagine, CV_BGR2GRAY);
		blur(imagine, imagine, Size(3, 3));
		Canny(imagine, imagine, 1, 50);

		imshow("Prima", imagine);

		int tasta = waitKey(1);
		if (tasta == 27)
			break;

	}

	cam.release();

	return 0;
}