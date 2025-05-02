#include "Canvas.h"
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <algorithm>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h), highlightedShape(nullptr) {
}

Canvas::~Canvas() {
    clear();
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
        std::cout << "Shape added. Total shapes: " << shapes.size() << std::endl;
    }
}

void Canvas::clear() {
    for (Shape* shape : shapes) {
        delete shape;
    }
    shapes.clear();
    highlightedShape = nullptr;
}

void Canvas::render() {
   
    for (Shape* shape : shapes) {
        if (shape) {
           shape->draw();
        }
    }

    
    if (highlightedShape) {
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(2.0f);

        
    }
}


Shape* Canvas::getShapeAt(float mx, float my) {
    
    for (int i = shapes.size() - 1; i >= 0; --i) {
        if (shapes[i] && shapes[i]->contains(mx, my)) {
            return shapes[i];
        }
    }
    return nullptr;
}

void Canvas::eraseAt(float x, float y, float eraseRadius) {
    
    for (int i = shapes.size() - 1; i >= 0; --i) {
        if (shapes[i] && shapes[i]->contains(x, y)) {
             
            if (shapes[i] == highlightedShape) {
                highlightedShape = nullptr;
            }
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
           
            return;
        }
    }
}



void Canvas::bringToFront(Shape* shape) {
    if (!shape || shapes.size() < 2) return;

    auto it = std::find(shapes.begin(), shapes.end(), shape);

    if (it != shapes.end()) {
        if (it != shapes.end() - 1) {
            Shape* foundShape = *it;
            shapes.erase(it);
            shapes.push_back(foundShape);
            std::cout << "Brought shape to front." << std::endl;
        }
    }
}

void Canvas::sendToBack(Shape* shape) {
    if (!shape || shapes.size() < 2) return;

    auto it = std::find(shapes.begin(), shapes.end(), shape);

    if (it != shapes.end()) {
        if (it != shapes.begin()) {
            Shape* foundShape = *it;
            shapes.erase(it);
            shapes.insert(shapes.begin(), foundShape);
             std::cout << "Sent shape to back." << std::endl;
        }
    }
}

void Canvas::setHighlightedShape(Shape* shape) {
    highlightedShape = shape;
}

// Working as of May 3 | ALso beautified code