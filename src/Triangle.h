#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
    float x, y;
    float size;
    float r, g, b;

    float v1x, v1y, v2x, v2y, v3x, v3y;
    void calculateVertices();

    float sign(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);

public:
    Triangle(float cx, float cy, float r, float g, float b);

    void draw() override;
    bool contains(float mx, float my) override;
    void setColor(float r, float g, float b) override;
};

#endif