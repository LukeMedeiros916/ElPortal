#include "Triangle.h"
#include <GL/freeglut.h>
#include <cmath>

const float SQRT3 = 1.7320508f;

void Triangle::calculateVertices() {
    float half_base = size / SQRT3;
    float height_part1 = size * (2.0f / 3.0f);
    float height_part2 = size * (1.0f / 3.0f);

    v1x = x;           v1y = y + height_part1;
    v2x = x - half_base; v2y = y - height_part2;
    v3x = x + half_base; v3y = y - height_part2;
}

Triangle::Triangle(float cx, float cy, float r_in, float g_in, float b_in) {
    x = cx;
    y = cy;
    r = r_in;
    g = g_in;
    b = b_in;
    size = 0.3f;
    calculateVertices();
}

void Triangle::draw() {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(v1x, v1y);
        glVertex2f(v2x, v2y);
        glVertex2f(v3x, v3y);
    glEnd();
}

float Triangle::sign(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y) {
    return (p1x - p3x) * (p2y - p3y) - (p2x - p3x) * (p1y - p3y);
}

bool Triangle::contains(float mx, float my) {
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(mx, my, v1x, v1y, v2x, v2y);
    d2 = sign(mx, my, v2x, v2y, v3x, v3y);
    d3 = sign(mx, my, v3x, v3y, v1x, v1y);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}


void Triangle::setColor(float r_in, float g_in, float b_in) {
    r = r_in;
    g = g_in;
    b = b_in;
}