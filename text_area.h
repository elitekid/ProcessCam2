#ifndef TEXT_AREA_H
#define TEXT_AREA_H

#include <iostream>
#include <cstring>

class TextArea {

 public:
  TextArea(int x, int y, const char* hex_color);
  ~TextArea();
  int GetX() const;
  int GetY() const;
  const char* GetHexColor() const;

 private:
  int x_;
  int y_;
  char hex_color_[7];
};

#endif // TEXT_AREA_H
