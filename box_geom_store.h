// Copyright 2024 elitekid

#ifndef BOX_GEOM_STORE_H_
#define BOX_GEOM_STORE_H_

#include <vector>

#include "frame_info.h"
#include "g_buffers.h"
#include "shader.h"

class BoxGeomStore {
 public:
  BoxGeomStore();
  ~BoxGeomStore();
  void SetBoxGeometry();
  void DrawBox(const FrameInfo& frame_info);
  void Bind();
  void UnBind();

 private:
  std::vector<float> vertices_;
  GBuffers box_buffers_;
  Shader box_shader_;
};

#endif  // BOX_GEOM_STORE_H_
