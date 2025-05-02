#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include <vector>

class Polygon : public Shape {
    float x, y;
    float radius;
    int sides;
    float r, g, b;

    std::vector<float> vertices_x;
    std::vector<float> vertices_y;
    void calculateVertices();

public:
    Polygon(float cx, float cy, float r, float g, float b, int n_sides = 5);

    void draw() override;
    bool contains(float mx, float my) override;
    void setColor(float r, float g, float b) override;
};

#endif