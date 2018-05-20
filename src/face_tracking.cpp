#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main() {


	CascadeClassifier clasificator;
	clasificator.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");

	VideoCapture captura;

	if (!captura.open(0)) {
		cout << "Nu am putut deschide camera!" << endl;
		getchar();
		return 0;
	}
	
	Mat imagine;
	Mat grayscaleFrame;
	Mat save_img;

	//Mat blur;
	//Mat canny;
	//Mat imgBlurred;

	namedWindow("Aplicatie Face Tracking", 1);
	//namedWindow("Webcam Canny", 2);

	while (true)
	{
		captura >> imagine;
		captura >> save_img;

		cvtColor(imagine, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);

		std::vector<Rect> fata;

		clasificator.detectMultiScale(grayscaleFrame, fata, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(70, 70));

		for (int i = 0; i < fata.size(); i++) {
			Point pt1(fata[i].x + fata[i].width, fata[i].y + fata[i].height);
			Point pt2(fata[i].x, fata[i].y);

			rectangle(imagine, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		}

		//GaussianBlur(grayscaleFrame, imgBlurred, Size(5 , 5), 1.8);
		//Canny(imgBlurred, canny, 1, 50);

		if (save_img.empty())
		{
			std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
		}
		// Save the frame into a file
		imwrite("C:/Users/Alex/Documents/GitHub/opencv/data/test.jpg", save_img);

		imshow("Aplicatie Face Tracking", imagine);
		//imshow("Webcam Canny", imagine);

		int tasta = waitKey(1);
		if (tasta == 27)
			break;
	}

	return 0;
}