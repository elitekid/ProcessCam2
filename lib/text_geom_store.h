// Copyright 2024 elitekid

#ifndef TEXT_GEOM_STORE_H_
#define TEXT_GEOM_STORE_H_

#include "g_buffers.h"
#include "shader.h"
#include "label_text_store.h"
#include "frame_info.h"
#include "util.h"
#include <vector>

class TextGeomStore
{
 public:

  TextGeomStore();
  ~TextGeomStore();
  void SetTextGeometry();
  void DeleteBuffers();
  void DrawColorCode(FrameInfo& frame_info);

 private:
  void AddLabel();
  void SetSimpleTriangle(float* vertices, unsigned int& vertices_count,
  	unsigned int* indices, unsigned int& indices_count);
  GBuffers tri_buffers_;
  LabelTextStore all_labels_;
  
  Shader tri_shader_;
  Shader text_shader_;
  
  SettingManager setting_manager_;
  FrameInfo frame_info_;
};

#endif  // TEXT_GEOM_STORE_H_