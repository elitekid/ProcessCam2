#include "textarea.h"
#include <iostream>
#include <cstring>

TextArea::TextArea(int xVal, int yVal, const char* hexColorVal) {
    x = xVal;
    y = yVal;
    setHexColor(hexColorVal);
}

int TextArea::getX() const {
    return x;
}

int TextArea::getY() const {
    return y;
}

const char* TextArea::getHexColor() const {
    return hexColor;
}

void TextArea::setX(int xVal) {
    x = xVal;
}

void TextArea::setY(int yVal) {
    y = yVal;
}

void TextArea::setHexColor(const char* hexColorVal) {
    std::strncpy(hexColor, (std::strlen(hexColorVal) == 6) ? hexColorVal : "000000", sizeof(hexColor) - 1);
    hexColor[sizeof(hexColor) - 1] = '\0';
}
