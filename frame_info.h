// Copyright 2024 elitekid

#ifndef FRAME_INFO_H_
#define FRAME_INFO_H_

#include <iostream>
#include <vector>
#include <concurrent_vector.h>
#include <opencv2/opencv.hpp>

#include "text_area.h"
#include "setting_manager.h"
#include "util.h"

class FrameInfo {
 public:
  FrameInfo();
 ~FrameInfo();
  void UpdateFrame(const cv::Mat& new_frame);
  void Clear();
  cv::Mat GetFrame() const;

  std::vector<float> GetVertices() const;
  int GetBoxCnt() const;
  float GetSquareSize() const;
  std::vector<TextArea> GetTextAreas() const;
 private:
  cv::Mat frame_;
  cv::Mat fgmask_;
  int box_cnt_;
  float square_size_;
  std::vector<float> vertices_;
  std::vector<TextArea> text_area_;
  
  cv::Ptr<cv::BackgroundSubtractorMOG2> fgbg_;
};

#endif  // FRAME_INFO_H_
