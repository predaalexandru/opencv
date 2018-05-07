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

	CascadeClassifier clasificator("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");

	Mat imagine;
	cvNamedWindow("Prima");

	vector <Rect> fete;

	while (1) {
		cam >> imagine;
		cvtColor(imagine, imagine, CV_BGR2GRAY);
		clasificator.detectMultiScale(imagine, fete);
		//blur(imagine, imagine, Size(3, 3));
		//Canny(imagine, imagine, 1, 50);

		for (int i = 0; i < fete.size(); i++)
			rectangle(imagine, Rect(Point(fete[i].x, fete[i].y), Point(Point(fete[i].width, fete[i].y + fete[i].height))), Scalar(0, 0, 255));

		imshow("Prima", imagine);

		int tasta = waitKey(1);
		if (tasta == 27)
			break;

	}

	cam.release();

	return 0;
}