#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include "Point.h"
#include <vector>

class Scribble : public Shape {
    std::vector<Point> points;
    float r, g, b;
    int size;

public:
    Scribble(float r, float g, float b, int size);

    void addPoint(float x, float y);

    void draw() override;
    bool contains(float mx, float my) override;
    void setColor(float r, float g, float b) override;
    void resize(float factor) override;
    void move(float dx, float dy) override;
};

#endif
// Used https://codebeautify.org/ to keep code readable and nice