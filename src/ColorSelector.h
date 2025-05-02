#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <bobcat_ui/all.h> 
#include "Color.h"
#include <functional> 


class ColorSelector : public bobcat::Group {
    Color selectedColor;
    float selectorX;
    bool dragging;

    void hsvToRgb(float h, float s, float v, float& r, float& g, float& b);
    Color getColorAtX(float localX);


public:
    ColorSelector(int x, int y, int w, int h, const char* label = 0);

    Color getColor() const;

    virtual void draw();
    virtual int handle(int event);

};

#endif

// Working as of May 3 | ALso beautified code