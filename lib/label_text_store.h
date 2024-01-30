// Copyright 2024 elitekid

#ifndef LABEL_TEXT_STORE_H_
#define LABEL_TEXT_STORE_H_

#include <iostream>
#include <glm/vec2.hpp>
#include "g_buffers.h"
#include "font_atlas.h"

struct LabelText
{
  // Store the individual label
  const char* label;
  glm::vec2 label_loc;
  glm::vec3 label_color;
  float label_angle;
  float label_size;
};

class LabelTextStore
{
	// Stores all the labels
 public:
  FontAtlas main_font_;
  unsigned int total_char_count_ = 0;
  GBuffers label_buffers_;
  std::vector<LabelText> labels_;
  
  LabelTextStore();
  ~LabelTextStore();
  void Init();
  void AddText(const char* text, glm::vec2 text_loc, glm::vec3 text_color, float geom_scale, float font_angle, float font_size);
  void SetBuffers();
  void ClearBuffers();
  void DrawColorCode();
 private:
  void GetBuffer(LabelText& label, float* vertices, unsigned int& vertex_index, unsigned int* indices, unsigned int& indices_index);
  glm::vec2 RotatePt(glm::vec2& rotate_about, glm::vec2 pt, float& rotation_angle);
};

#endif  // LABEL_TEXT_STORE_H_