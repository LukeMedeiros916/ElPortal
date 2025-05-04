#include "Circle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <algorithm>

Circle::Circle() {
    x = 0.0;
    y = 0.0;
    radius = 0.2;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Circle::Circle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    radius = 0.2;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Circle::draw() {
    glColor3f(r, g, b);
    const int segments = 64;
    const float angle_increment = 2.0f * M_PI / segments;

    glBegin(GL_POLYGON);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * angle_increment;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

bool Circle::contains(float mx, float my) {
    float dx = mx - x;
    float dy = my - y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

void Circle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Circle::resize(float factor) {
    const float minRadius = 0.01f;
    radius = std::max(minRadius, radius * factor);
}

void Circle::move(float dx, float dy) {
    x += dx;
    y += dy;
}