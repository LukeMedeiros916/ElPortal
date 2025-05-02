#include "Application.h"
#include "Enums.h"
#include <iostream> // Include necessary headers if missing

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();
    float eraserSize = 0.05; // Define eraser size

    if (tool == PENCIL) {
        canvas->addPoint(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->eraseAt(mx, my, eraserSize); // Call eraseAt
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
    }
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();
    float eraserSize = 0.05; // Define eraser size

    if (tool == PENCIL) {
        canvas->addPoint(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->eraseAt(mx, my, eraserSize); // Call eraseAt
        canvas->redraw();
    }
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
        selectedShape = nullptr; // Also deselect shape on clear
        canvas->redraw();
    }
}

void Application::onColorSelectorChange(bobcat::Widget* sender) {
    Color color = colorSelector->getColor();

    if (selectedShape) {
        cout << "Update selected shape color" << endl;
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
}

Application::Application() {
    window = new Window(25, 75, 400, 400, "Lecture 21");

    selectedShape = nullptr;

    toolbar = new Toolbar(0, 0, 50, 400);
    canvas = new Canvas(50, 0, 350, 350);
    colorSelector = new ColorSelector(50, 350, 350, 50);
    colorSelector->box(FL_BORDER_BOX);

    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(colorSelector, Application::onColorSelectorChange);

    window->show();
}

// Destructor might be needed to delete allocated objects like window, toolbar, etc.
// Application::~Application() { ... delete members ... }