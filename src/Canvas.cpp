#include "Canvas.h"
#include "Circle.h"
#include <GL/freeglut.h>
#include <iostream> // Include necessary headers if missing

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    // Constructor body if needed
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

    for (int i = shapes.size() - 1; i >= 0; --i) { // Iterate backwards to select topmost shape first
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

// Added this method implementation
void Canvas::eraseAt(float x, float y, float eraseRadius) {
    for (int i = shapes.size() - 1; i >= 0; --i) {
        if (shapes[i]->contains(x, y)) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
            // Remove 'break;' if you want to erase multiple overlapping shapes with one click
            break;
        }
    }

    float eraseRadiusSq = eraseRadius * eraseRadius;
    for (int i = points.size() - 1; i >= 0; --i) {
        float dx = points[i]->getX() - x;
        float dy = points[i]->getY() - y;
        float distSq = dx * dx + dy * dy;
        if (distSq <= eraseRadiusSq) {
            delete points[i];
            points.erase(points.begin() + i);
        }
    }
}