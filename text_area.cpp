#include "text_area.h"

TextArea::TextArea(int x, int y, const char* hex_color) : x_(x), y_(y) {
  std::strncpy(hex_color_, (std::strlen(hex_color) == 6) ? hex_color : "000000",
               sizeof(hex_color_) - 1);
  hex_color_[sizeof(hex_color_) - 1] = '\0';
}

TextArea::~TextArea() {}

int TextArea::GetX() const {
    return x_;
}

int TextArea::GetY() const {
    return y_;
}

const char* TextArea::GetHexColor() const {
    return hex_color_; 
}