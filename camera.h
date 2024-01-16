#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;

class Camera 
{
public:
    Camera();
    ~Camera();

    void initialize(int camNum);
    Mat getFrame();
    void stop();
    int getCols() const;
    int getRows() const;
private:
    Mat frame;
    VideoCapture cap;
    bool status;
};