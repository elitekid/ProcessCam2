// Copyright 2024 elitekid

#ifndef CAM_GEOM_STORE_H_
#define CAM_GEOM_STORE_H_

#include <opencv2/opencv.hpp>

#include "g_buffers.h"
#include "setting_manager.h"
#include "shader.h"
#include "texture.h"

// OpenCV 네임스페이스 직접 사용하지 않음

class CamGeomStore {
 public:
  CamGeomStore();
  ~CamGeomStore();

  void SetCameraGeometry(int width, int height);
  void DrawCam(const cv::Mat& frame);
  void Bind();
  void UnBind();

 private:
  GBuffers cam_buffers_;
  Shader cam_shader_;
  Texture cam_texture_;
  SettingManager setting_manager_;
};

#endif  // CAM_GEOM_STORE_H_