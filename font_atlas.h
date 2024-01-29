// Copyright 2024 elitekid

#ifndef FONT_ATLAS_H_
#define FONT_ATLAS_H_

#include <iostream>
#include <windows.h>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <QDebug>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

#include "setting_manager.h"
#include "g_buffers.h"
/// FreeType을 사용하여 로드된 글자와 관련된 모든 상태 정보를 보유하는 구조체
struct Character
{
  glm::ivec2 size;     // 글리프의 크기 (폭 및 높이)
  glm::ivec2 bearing;  // 베이스라인에서 글리프의 왼쪽/위쪽 오프셋
  
  // 주의: 어드밴스(Advance)는 1/64 픽셀의 수입니다.
  // (ch.Advance >> 6) // 6비트 오른쪽으로 시프트하여 픽셀 값으로 변환 (2^6 = 64)
  unsigned int advance;  // 다음 글리프로 전진하기 위한 수평 오프셋
  
  glm::vec2 top_left;   // 아틀라스에서 이 문자의 위치 - 좌상단 [0,0]
  glm::vec2 bot_right;  // 아틀라스에서 이 문자의 위치 - 우하단 [1,1]
};

class FontAtlas
{
 public:
  FontAtlas();
  ~FontAtlas();
  
  // 아틀라스를 생성하는 함수
  void CreateAtlas();
  
  SettingManager setting_manager_;
  unsigned int texture_id_;      // 텍스처 식별자
  unsigned int texture_width_;   // 아틀라스의 전체 너비
  unsigned int texture_height_;  // 아틀라스의 전체 높이
  std::map<char, Character> ch_atlas_;  // 문자와 그에 대한 정보를 매핑하는 맵
 private:
  std::string GetWindowsDrive();
  bool is_created_;						// 아틀라스 생성 여부 플래그
};

#endif  // FONT_ATLAS_H_