#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cam;
	if (!cam.open(0)) {
		cout << "Nu am putut deschide camera!"<<endl;
		getchar();
		return 0;
	}
	 
	Mat imagine;
	cvNamedWindow("Prima");

	while (1) {
		cam >> imagine;
		
		imshow("Prima", imagine);

		int tasta = waitKey(1);
		if (tasta == 27)
			break;

	}
	return 0;
}