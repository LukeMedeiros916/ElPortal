#include "Application.h"
#include "Enums.h"
#include "Scribble.h"
#include <iostream>


using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();
    float eraserSize = 0.05;
    int pencilSize = 3;

    selectedShape = nullptr;
    currentScribble = nullptr;

    if (tool == PENCIL) {
        currentScribble = new Scribble(color.getR(), color.getG(), color.getB(), pencilSize);
        currentScribble->addPoint(mx, my);
        canvas->addShape(currentScribble);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->eraseAt(mx, my, eraserSize);
        canvas->redraw();
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == CIRCLE) {
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == MOUSE) {
        selectedShape = canvas->getSelectedShape(mx, my);

        canvas->redraw();
    }
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    float eraserSize = 0.05;

    if (tool == PENCIL) {
        if (currentScribble) {
            currentScribble->addPoint(mx, my);
            canvas->redraw();
        }
    }
    else if (tool == ERASER) {
        canvas->eraseAt(mx, my, eraserSize);
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();

    if (tool == PENCIL) {
        if (currentScribble) {
            currentScribble = nullptr;
            canvas->redraw();
        }
    }
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
        selectedShape = nullptr;
        currentScribble = nullptr;
        canvas->redraw();
    }
    selectedShape = nullptr;
    currentScribble = nullptr;
}


void Application::onColorSelectorChange(bobcat::Widget* sender) {

    Color color = colorSelector->getColor();

    if (selectedShape) {
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
}

Application::Application() {
    window = new Window(25, 75, 400, 400, "Lecture 21");

    selectedShape = nullptr;
    currentScribble = nullptr;

    toolbar = new Toolbar(0, 0, 50, 400);
    canvas = new Canvas(50, 0, 350, 350);


    colorSelector = new ColorSelector(50, 350, 350, 50, "");


    window->add(toolbar);
    window->add(canvas);


    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_CHANGE(toolbar, Application::onToolbarChange);


    ON_CHANGE(colorSelector, Application::onColorSelectorChange);

    window->show();
}

// Working as of May 2