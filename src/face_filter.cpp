#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


/** @function main */
int main()
{
	CascadeClassifier fata_clasificator, ochi_clasificator;
	if (!fata_clasificator.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml")) {
		cout << "Nu am putut deschide fisierul!" << endl;
		getchar();
		return 0;
	}
	if (!ochi_clasificator.load("C:/opencv/sources/data/haarcascades/haarcascade_eye.xml")) {
		cout << "Nu am putut deschide fisierul!" << endl;
		getchar();
		return 0;
	}
	VideoCapture captura;
	if (!captura.open(0))
	{
		cout << "Nu am putut deschide camera!" << endl;
		getchar();
		return 0;
	}

	Mat imagine;
	Mat	gray_imagine;
	Mat save_img;
	vector<Rect> fata, ochi;

	namedWindow("Aplicatie Face Tracking", 1);

	while (1)
	{
		captura >> imagine;
		captura >> save_img;
		
		cvtColor(imagine, gray_imagine, CV_BGR2GRAY);
		equalizeHist(gray_imagine, gray_imagine);
		fata_clasificator.detectMultiScale(gray_imagine, fata, 1.1, 3, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(300, 300));
		for (int i = 0; i < fata.size(); i++)
		{
			Point pt1(fata[i].x + fata[i].width, fata[i].y + fata[i].height);
			Point pt2(fata[i].x, fata[i].y);

			Mat faceROI = gray_imagine(fata[i]);
			ochi_clasificator.detectMultiScale(faceROI, ochi, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
			for (size_t j = 0; j< ochi.size(); j++)
			{
				Point center(fata[i].x + ochi[j].x + ochi[j].width*0.5, fata[i].y + ochi[j].y + ochi[j].height*0.5);
				int radius = cvRound((ochi[j].width + ochi[j].height)*0.25);
				circle(imagine, center, radius, Scalar(255, 0, 0), 2, 8, 0);
			}
			rectangle(imagine, pt1, pt2, cvScalar(0, 255, 0), 2, 8, 0);
		}

		if (save_img.empty())
		{
			cout << "Ceva este in neregula cu webcam-ul, nu am putut face poza" << endl;
		}
		imwrite("C:/Users/Alex/Documents/GitHub/opencv/data/test.jpg", save_img);

		imshow("Aplicatie Face Tracking", imagine);
		
		int tasta = waitKey(1);
		if (tasta == 27)
			break;
	}
	return 0;
}