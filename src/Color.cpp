#include "Color.h"
#include <cmath>

Color::Color() {
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

float Color::getR() const {
    return r;
}

float Color::getG() const {
    return g;
}

float Color::getB() const {
    return b;
}

void Color::setR(float r) {
    this->r = r;
}
void Color::setG(float g) {
    this->g = g;
}
void Color::setB(float b) {
    this->b = b;
}

// Working as of May 3 | ALso beautified code