#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape{
    float x;
    float y;
    float radius;
    float r;
    float g;
    float b;

public:
    Circle();
    Circle(float x, float y, float r, float g, float b);
    void draw();
    bool contains(float mx, float my);
    void setColor(float r, float g, float b);
};

#endif