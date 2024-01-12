#ifndef TEXTAREA_H
#define TEXTAREA_H

class TextArea {
private:
    int x;
    int y;
    char hexColor[7];

public:
    int getX() const;
    int getY() const;
    const char* getHexColor() const;

    void setX(int xVal);
    void setY(int yVal);
    void setHexColor(const char* hexColorVal);
    TextArea(int xVal, int yVal, const char* hexColorVal);
};

#endif // TEXTAREA_H
