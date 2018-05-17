#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;
using namespace std;


int main() {
	cv::VideoCapture capWebcam(0);            

	if (capWebcam.isOpened() == false) {                                
		cout << "Nu am putut deschide camera!" << endl;      
		getchar();                                                           
		return(0);                                                          
	}

	cv::Mat imgOriginal;        
	cv::Mat imgGrayscale;       
	cv::Mat imgBlurred;         
	cv::Mat imgCanny;           

	char charCheckForEscKey = 0;

	while (charCheckForEscKey != 27 && capWebcam.isOpened()) {           
		bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);           

		if (!blnFrameReadSuccessfully || imgOriginal.empty()) {                 
			cout << "Nu se poate citi de la Webcam\n";                 
			break;                                                             
		}

		cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);                

		cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.8);                      

		cv::Canny(imgBlurred, imgCanny, 50, 100);                             


		cv::namedWindow("Webcam Original", CV_WINDOW_NORMAL);       
		cv::namedWindow("Webcam Canny", CV_WINDOW_NORMAL);          
																
		cv::imshow("Webcam Original", imgOriginal);                 
		cv::imshow("Webcam Canny", imgCanny);                     

		charCheckForEscKey = cv::waitKey(1);        
	}   

	return(0);
}
