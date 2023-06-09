#pragma once

#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"


using namespace cv;
using namespace std;

class BackgroundRemover {
	public:
		BackgroundRemover(void);
		void calibrate(Mat input);
		Mat getForeground(Mat input);

	private:
		Mat background;
		bool calibrated = false;

		Mat getForegroundMask(Mat input);
		void removeBackground(Mat input, Mat background);
};