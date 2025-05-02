#include "Point.h"

Point::Point() {
    x = 0.0;
    y = 0.0;
}

Point::Point(float x, float y) : Point() {
    this->x = x;
    this->y = y;
}


float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

// Working as of May 3 | ALso beautified code