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

	VideoWriter video("C:/Users/Alex/Documents/GitHub/opencv/data/film.avi", CV_FOURCC('D', 'I', 'V', 'X'), 10, Size(cam.get(3), cam.get(4)), true);

	if (!video.isOpened())
	{
		cout << "Nu am putut deschide fisier video!" << endl;
		getchar();
		return 0;
	}

	Mat imagine;
	cvNamedWindow("Prima");

	while (1) {
		cam >> imagine;

		video << imagine;

		imshow("Prima", imagine);

		int tasta = waitKey(1);
		if (tasta == 27)
			break;

	}

	cam.release();
	video.release();

	return 0;
}