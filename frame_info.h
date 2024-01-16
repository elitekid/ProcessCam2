#pragma once
#include "textarea.h"
#include "SettingManager.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <concurrent_vector.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class frame_info
{
public:
	frame_info();
	~frame_info();

	void updateFrame(const Mat& newFrame);
	void clear();

	Mat getFrame() const;
	vector<float> getVertices() const;
	int getBoxCnt() const;
	float getSquareSize() const;
	vector<TextArea> getTextAreas() const;
private:
	Mat frame;
	Mat fgmask;
	int boxCnt;
	float squareSize;
	vector<float> vertices;
	vector<TextArea> textAreas;

	Ptr<BackgroundSubtractorMOG2> fgbg;
};
