#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"

#include "shape.h"
#include "Tracker.h"

using namespace cv;
using namespace std;
int main(int, char **)
{
	VideoCapture videoCapture(0);
	videoCapture.set(CAP_PROP_SETTINGS, 1);

	if (!videoCapture.isOpened())
	{
		cout << "Can't find camera!" << endl;
		return -1;
	}

	Mat frame, frameOut, handMask, foreground, fingerCountDebug;

	Mat TrackPrint(600, 800, CV_8UC3);
	TrackPrint = Scalar::all(0);

	BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	FingerCount fingerCount;

	while (true)
	{
		videoCapture >> frame;
		frameOut = frame.clone();

		skinDetector.drawSkinColorSampler(frameOut);

		foreground = backgroundRemover.getForeground(frame);

		faceDetector.removeFaces(frame, foreground);
		handMask = skinDetector.getSkinMask(foreground);
		fingerCountDebug = fingerCount.findFingersCount(handMask, frameOut);

		imshow("output", frameOut);
		imshow("foreground", foreground);
		imshow("handMask", handMask);
		imshow("handDetection", fingerCountDebug);
		imshow("printTrack", TrackPrint);

		namedWindow("【滚动条窗口】", 0);
		createTrackbar("thick", "【滚动条窗口】", &thick, 100, 0);
		createTrackbar("Blue", "【滚动条窗口】", &dgBlue, 255, 0);
		createTrackbar("Green", "【滚动条窗口】", &dgGreen, 255, 0);
		createTrackbar("Red", "【滚动条窗口】", &dgRed, 255, 0);

		if (fingerCount.final_points.size() > 0)
			printTrack(fingerCount.getHighest(), TrackPrint);
		// cout << fingerCount.final_points.size() << ' ';
		int key = waitKey(1);

		if (key == 27) // esc
			break;
		else if (key == 98) // b
			backgroundRemover.calibrate(frame);
		else if (key == 115) // s
			skinDetector.calibrate(frame);
		else if (key == 't')
		{
			state = 1;
			Track.clear();
			TrackPrint = Scalar::all(0);
		}
		else if (key == 'a')
		{
			state = 2;
			shape_analysis(Track);
		}
	}
	return 0;
}