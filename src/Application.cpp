#include "Application.h"
#include "Enums.h"
#include "Scribble.h"
#include "Shape.h"
#include <iostream>

using namespace bobcat;
using namespace std;


void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL currentTool = toolbar->getTool();
    Color color = colorSelector->getColor();
    float eraserSize = 0.05;
    int pencilSize = 3;

    
    if (currentTool != MOUSE) {
         if (selectedShape) {
             selectedShape = nullptr;
             canvas->setHighlightedShape(nullptr);
             
         }
    }
    currentScribble = nullptr;

    
    if (currentTool == PENCIL) {
        currentScribble = new Scribble(color.getR(), color.getG(), color.getB(), pencilSize);
        currentScribble->addPoint(mx, my);
        canvas->addShape(currentScribble);
    } else if (currentTool == ERASER) {
        Shape* shapeToErase = canvas->getShapeAt(mx, my);
        if (shapeToErase == selectedShape) {
             selectedShape = nullptr;
             canvas->setHighlightedShape(nullptr);
        }
        canvas->eraseAt(mx, my, eraserSize);
    } else if (currentTool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
    } else if (currentTool == CIRCLE) {
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
    } else if (currentTool == TRIANGLE) {
        canvas->addTriangle(mx, my, color.getR(), color.getG(), color.getB());
    } else if (currentTool == POLYGON) {
        canvas->addPolygon(mx, my, color.getR(), color.getG(), color.getB());
    } else if (currentTool == MOUSE) {
        Shape* newlySelected = canvas->getShapeAt(mx, my);
        if (newlySelected != selectedShape) {
            selectedShape = newlySelected;
            canvas->setHighlightedShape(selectedShape);
            canvas->redraw();
        }
        if (selectedShape) {
             std::cout << "Application: Selected a shape." << std::endl;
        } else {
             std::cout << "Application: Clicked empty area with mouse tool." << std::endl;
        }
    }

    if (currentTool != MOUSE) {
        canvas->redraw();
    }
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL currentTool = toolbar->getTool();
    float eraserSize = 0.05;

    if (currentTool == PENCIL) {
        if (currentScribble) {
            currentScribble->addPoint(mx, my);
            canvas->redraw();
        }
    } else if (currentTool == ERASER) {
         Shape* shapeToErase = canvas->getShapeAt(mx, my);
         if (shapeToErase == selectedShape) {
              selectedShape = nullptr;
              canvas->setHighlightedShape(nullptr);
         }
        canvas->eraseAt(mx, my, eraserSize);
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    TOOL currentTool = toolbar->getTool();
    if (currentTool == PENCIL) {
        currentScribble = nullptr;
    }
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    Toolbar* changedToolbar = dynamic_cast<Toolbar*>(sender);
    if (!changedToolbar) return;

    ACTION action = changedToolbar->getAction();
    TOOL tool = changedToolbar->getTool();

    std::cout << "Application: Toolbar change detected. Action=" << action << std::endl;

    if (changedToolbar == rightToolbar) {
        const float zoomInFactor = 1.1f;
        const float zoomOutFactor = 1.0f / zoomInFactor;

        if (action == BRING_FRONT) {
            if (selectedShape) {
                canvas->bringToFront(selectedShape);
                canvas->redraw();
            }
        } else if (action == SEND_BACK) {
            if (selectedShape) {
                canvas->sendToBack(selectedShape);
                canvas->redraw();
            }
        
        } else if (action == ZOOM_IN) {
            if (selectedShape) {
                std::cout << "Application: Resizing shape larger." << std::endl;
                selectedShape->resize(zoomInFactor);
                canvas->redraw();
            } else {
                 std::cout << "Application: Zoom In clicked but no shape selected." << std::endl;
            }
        } else if (action == ZOOM_OUT) {
            if (selectedShape) {
                std::cout << "Application: Resizing shape smaller." << std::endl;
                selectedShape->resize(zoomOutFactor);
                canvas->redraw();
            } else {
                 std::cout << "Application: Zoom Out clicked but no shape selected." << std::endl;
            }
        }
        changedToolbar->resetAction();
    }
    else if (changedToolbar == toolbar) {
        if (action == CLEAR) {
            canvas->clear();
            selectedShape = nullptr;
            currentScribble = nullptr;
            canvas->setHighlightedShape(nullptr);
            canvas->redraw();
            changedToolbar->resetAction();
        } else {
             if (tool != MOUSE) {
                if (selectedShape) {
                     selectedShape = nullptr;
                     canvas->setHighlightedShape(nullptr);
                     canvas->redraw();
                }
             }
            changedToolbar->resetAction();
        }
        currentScribble = nullptr;
    }
}

void Application::onColorSelectorChange(bobcat::Widget* sender) {
    Color color = colorSelector->getColor();
    if (selectedShape) {
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
}


Application::Application() :
    window(nullptr), toolbar(nullptr), rightToolbar(nullptr),
    canvas(nullptr), colorSelector(nullptr),
    selectedShape(nullptr), currentScribble(nullptr)
{
    int leftToolbarWidth = 50; int rightToolbarWidth = 50; int canvasWidth = 350;
    int windowWidth = leftToolbarWidth + canvasWidth + rightToolbarWidth;
    int windowHeight = 400; int colorSelectorHeight = 50;
    int canvasHeight = windowHeight - colorSelectorHeight;
    window = new Window(25, 75, windowWidth, windowHeight, "El Portal Drawing App");

    toolbar = new Toolbar(0, 0, leftToolbarWidth, windowHeight, true);
    canvas = new Canvas(leftToolbarWidth, 0, canvasWidth, canvasHeight);
    colorSelector = new ColorSelector(leftToolbarWidth, canvasHeight, canvasWidth, colorSelectorHeight, "");
    int rightToolbarX = leftToolbarWidth + canvasWidth;
    rightToolbar = new Toolbar(rightToolbarX, 0, rightToolbarWidth, windowHeight, false);

    window->add(toolbar); window->add(canvas);
    window->add(colorSelector); window->add(rightToolbar);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(rightToolbar, Application::onToolbarChange);
    ON_CHANGE(colorSelector, Application::onColorSelectorChange);

    window->show();
}

Application::~Application() {
    delete window;
    std::cout << "Application destroyed." << std::endl;
}

// Working as of May 3 | ALso beautified code