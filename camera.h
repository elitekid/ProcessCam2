#ifndef CAMERA_H_
#define CAMERA_H_

#include <opencv2/opencv.hpp>

class Camera 
{
 public:
  Camera();
  ~Camera();
  
  void Init(int cam_num);
  cv::Mat GetFrame();
  void Stop();
  int GetCols() const;
  int GetRows() const;
 private:
  cv::Mat frame_;
  cv::VideoCapture cap_;
  bool status_;
};

#endif  // CAMERA_H_