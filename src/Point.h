#ifndef POINT_H
#define POINT_H

class Point {
    float x;
    float y;

public:
    Point();
    Point(float x, float y);

    float getX() const;
    float getY() const;

    void setX(float newX);
    void setY(float newY);
};

#endif
// Used https://codebeautify.org/ to keep code readable and nice