#pragma once
#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"

using namespace cv;
using namespace std;

class SkinDetector {
	public:
		SkinDetector(void);

		void drawSkinColorSampler(Mat input);
		void calibrate(Mat input);
		Mat getSkinMask(Mat input);

	private:
		int hLowThreshold = 0;
		int hHighThreshold = 0;
		int sLowThreshold = 0;
		int sHighThreshold = 0;
		int vLowThreshold = 0;
		int vHighThreshold = 0;

		bool calibrated = false;

		Rect skinColorSamplerRectangle1, skinColorSamplerRectangle2;

		void calculateThresholds(Mat sample1, Mat sample2);
		void performOpening(Mat binaryImage, int structuralElementShapde, Point structuralElementSize);
};