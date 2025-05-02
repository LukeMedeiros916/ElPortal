#include "Canvas.h"
#include "Circle.h"
#include <GL/freeglut.h>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    // 
}

void Canvas::addPoint(float x, float y, float r, float g, float b, int size) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Rectangle(x, y, r, g, b));
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Circle(x, y, r, g, b));
}

void Canvas::clear() {
    for (unsigned int i = 0 ; i < points.size(); i++) {
        delete points[i];
    }
    points.clear();

    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();
}

void Canvas::render() {
    for (unsigned int i = 0 ; i < points.size(); i++) {
        points[i]->draw();
    }

    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
}

Shape* Canvas::getSelectedShape(float mx, float my) {
    Shape* selectedShape = nullptr;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        // ask every shape if we clicked on it
        if (shapes[i]->contains(mx, my)) {
            std::cout << "Clicked on shape[" << i << "]" << std::endl;
            selectedShape = shapes[i];
            break;
        }
    }

    if (selectedShape == nullptr) {
        std::cout << "No selected shape" << std::endl;
    }

    return selectedShape;
}