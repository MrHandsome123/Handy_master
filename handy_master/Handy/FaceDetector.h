#pragma once

#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"


using namespace cv;
using namespace std;

class FaceDetector {
	public:
		FaceDetector(void);
		void removeFaces(Mat input, Mat output);
};