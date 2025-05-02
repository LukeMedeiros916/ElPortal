#include "Canvas.h"
#include <GL/freeglut.h>
#include <iostream>


Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {

}


void Canvas::addRectangle(float x, float y, float r, float g, float b) {

    addShape(new Rectangle(x, y, r, g, b));
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {

    addShape(new Circle(x, y, r, g, b));
}

void Canvas::addTriangle(float x, float y, float r, float g, float b) {
    addShape(new Triangle(x, y, r, g, b));
}

void Canvas::addPolygon(float x, float y, float r, float g, float b) {
    addShape(new Polygon(x, y, r, g, b));
}

void Canvas::addShape(Shape* shape) {
    if (shape != nullptr) {
        shapes.push_back(shape);
    }
}


void Canvas::clear() {


    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();
}

void Canvas::render() {


    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        if (shapes[i]) {
           shapes[i]->draw();
        }
    }
}

Shape* Canvas::getSelectedShape(float mx, float my) {
    Shape* selectedShape = nullptr;

    for (int i = shapes.size() - 1; i >= 0; --i) {
        if (shapes[i]->contains(mx, my)) {

            selectedShape = shapes[i];
            break;
        }
    }


    return selectedShape;
}


void Canvas::eraseAt(float x, float y, float eraseRadius) {

    for (int i = shapes.size() - 1; i >= 0; --i) {
        if (shapes[i]->contains(x, y)) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);

        }
    }

}