#include "Rectangle.h"
#include <GL/freeglut.h>
#include <algorithm>

Rectangle::Rectangle() {
    x = 0.0;
    y = 0.0;
    width = 0.4;
    height = 0.4;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Rectangle::Rectangle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    width = 0.4;
    height = 0.4;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::draw() {
    glColor3f(r, g, b);
    float half_width = width / 2.0f;
    float half_height = height / 2.0f;

    glBegin(GL_POLYGON);
        glVertex2f(x - half_width, y + half_height);
        glVertex2f(x + half_width, y + half_height);
        glVertex2f(x + half_width, y - half_height);
        glVertex2f(x - half_width, y - half_height);
    glEnd();
}

bool Rectangle::contains(float mx, float my) {
    float half_width = width / 2.0f;
    float half_height = height / 2.0f;
    bool within_x = (mx >= x - half_width) && (mx <= x + half_width);
    bool within_y = (my >= y - half_height) && (my <= y + half_height);
    return within_x && within_y;
}

void Rectangle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::resize(float factor) {
    const float minDimension = 0.01f;
    width = std::max(minDimension, width * factor);
    height = std::max(minDimension, height * factor);
}

void Rectangle::move(float dx, float dy) {
    x += dx;
    y += dy;
}