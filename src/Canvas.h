#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Rectangle.h"
#include "Circle.h"
#include "Scribble.h" 
#include "Shape.h"

class Canvas : public bobcat::Canvas_ {
    std::vector<Shape*> shapes;

public:
    Canvas(int x, int y, int w, int h);

    void addRectangle(float x, float y, float r, float g, float b);
    void addCircle(float x, float y, float r, float g, float b);
    void addShape(Shape* shape);

    void clear();
    void render();
    Shape* getSelectedShape(float mx, float my);
    void eraseAt(float x, float y, float eraseRadius);
};

#endif