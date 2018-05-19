#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat imagine );

/** Global variables */
//CascadeClassifier clasificator_fata("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
//CascadeClassifier clasificator_ochi("C:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml");
String face_cascade_name = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "C:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

/** @function main */
int main( void )
{
    VideoCapture capture;
    Mat imagine;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) )
	{ 
		printf("--(!)Error loading face cascade\n"); 
		return -1; 
	};
    if( !eyes_cascade.load( eyes_cascade_name ) )
	{ 
		printf("--(!)Error loading eyes cascade\n"); 
		return -1; 
	};

    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) 
	{ 
		printf("--(!)Error opening video capture\n"); 
		return -1; 
	}

    while (  capture.read(imagine) )
    {
        if(imagine.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay(imagine);

        int c = waitKey(1);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat imagine)
{
    std::vector<Rect> fete;
    

    cvtColor(imagine, imagine, CV_BGR2GRAY);
    equalizeHist(imagine, imagine);

    //-- Detect faces
    face_cascade.detectMultiScale(imagine, fete);

    for( size_t i = 0; i < fete.size(); i++ )
    {
        Point center(fete[i].x + fete[i].width/2, fete[i].y + fete[i].height/2 );
        ellipse( imagine, center, Size(fete[i].width/2, fete[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = imagine(fete[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        for( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center(fete[i].x + eyes[j].x + eyes[j].width/2, fete[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( imagine, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    imshow( window_name, imagine);
}