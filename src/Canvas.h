#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Rectangle.h"
#include "Circle.h"
#include "Scribble.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Shape.h"

class Canvas : public bobcat::Canvas_ {
    std::vector<Shape*> shapes;
    Shape* highlightedShape;

public:
    Canvas(int x, int y, int w, int h);
    ~Canvas();

    void addRectangle(float x, float y, float r, float g, float b);
    void addCircle(float x, float y, float r, float g, float b);
    void addTriangle(float x, float y, float r, float g, float b);
    void addPolygon(float x, float y, float r, float g, float b);
    void addShape(Shape* shape);

    void clear();
    void render() override;
    Shape* getShapeAt(float mx, float my);
    void eraseAt(float x, float y, float eraseRadius);

    void bringToFront(Shape* shape);
    void sendToBack(Shape* shape);
    void setHighlightedShape(Shape* shape);

};

#endif

// Working as of May 3 | ALso beautified code