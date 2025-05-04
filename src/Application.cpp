#include "Application.h"
#include "Enums.h"
#include "Scribble.h"
#include "Shape.h"
#include <iostream>
#include <FL/Fl_Widget.H>

using namespace bobcat;
using namespace std;


void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL currentTool = toolbar->getTool();
    Color color = colorSelector->getColor();
    float eraserSize = 0.05;
    int pencilSize = 3;

    isDraggingShape = false;
    currentScribble = nullptr;

    if (currentTool == MOUSE) {
        Shape* newlySelected = canvas->getShapeAt(mx, my);
        if (newlySelected) {
            selectedShape = newlySelected;
            canvas->setHighlightedShape(selectedShape);
            isDraggingShape = true;
            lastMouseX = mx;
            lastMouseY = my;
            std::cout << "[DEBUG] MouseDown: Selected a shape. Address: " << selectedShape << std::endl;
        } else {
            if (selectedShape) {
                std::cout << "[DEBUG] MouseDown: Deselected a shape." << std::endl;
                selectedShape = nullptr;
                canvas->setHighlightedShape(nullptr);
            } else {
                 std::cout << "[DEBUG] MouseDown: Clicked empty area." << std::endl;
            }
        }
        canvas->redraw();

    } else {
         if (selectedShape) {
             std::cout << "[DEBUG] MouseDown: Deselected shape due to tool change/draw." << std::endl;
             selectedShape = nullptr;
             canvas->setHighlightedShape(nullptr);
         }

        if (currentTool == PENCIL) {
            currentScribble = new Scribble(color.getR(), color.getG(), color.getB(), pencilSize);
            currentScribble->addPoint(mx, my);
            canvas->addShape(currentScribble);
        } else if (currentTool == ERASER) {
            canvas->eraseAt(mx, my, eraserSize);
        } else if (currentTool == RECTANGLE) {
            canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
        } else if (currentTool == CIRCLE) {
            canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
        } else if (currentTool == TRIANGLE) {
            canvas->addTriangle(mx, my, color.getR(), color.getG(), color.getB());
        } else if (currentTool == POLYGON) {
            canvas->addPolygon(mx, my, color.getR(), color.getG(), color.getB());
        }
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
    } else if (currentTool == MOUSE && isDraggingShape && selectedShape) {
        float dx = mx - lastMouseX;
        float dy = my - lastMouseY;
        selectedShape->move(dx, dy);
        lastMouseX = mx;
        lastMouseY = my;
        canvas->redraw();
    } else if (currentTool == ERASER) {
         Shape* shapeToErase = canvas->getShapeAt(mx, my);
         if (shapeToErase == selectedShape) {
              selectedShape = nullptr;
              isDraggingShape = false;
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

    if (isDraggingShape) {
        isDraggingShape = false;
        std::cout << "[DEBUG] MouseUp: Drag ended." << std::endl;
    }
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    Toolbar* changedToolbar = dynamic_cast<Toolbar*>(sender);
    if (!changedToolbar) return;

    ACTION action = changedToolbar->getAction();
    TOOL tool = changedToolbar->getTool();

    std::cout << "[DEBUG] ToolbarChange: Detected. Action=" << action << std::endl;

    if (changedToolbar == rightToolbar) {
        const float zoomInFactor = 1.1f;
        const float zoomOutFactor = 1.0f / zoomInFactor;

        bool needsRedraw = false;
        if (selectedShape) {
             std::cout << "[DEBUG] ToolbarChange: Right toolbar action with shape selected. Address: " << selectedShape << std::endl;
            if (action == BRING_FRONT) { canvas->bringToFront(selectedShape); needsRedraw = true; }
            else if (action == SEND_BACK) { canvas->sendToBack(selectedShape); needsRedraw = true; }
            else if (action == ZOOM_IN) { selectedShape->resize(zoomInFactor); needsRedraw = true; }
            else if (action == ZOOM_OUT) { selectedShape->resize(zoomOutFactor); needsRedraw = true; }
        } else {
             std::cout << "[DEBUG] ToolbarChange: Right toolbar action but NO shape selected." << std::endl;
        }

        if(needsRedraw) canvas->redraw();
        changedToolbar->resetAction();

    } else if (changedToolbar == toolbar) {
        if (action == CLEAR) {
            std::cout << "[DEBUG] ToolbarChange: Clear action." << std::endl;
            canvas->clear();
            selectedShape = nullptr;
            currentScribble = nullptr;
            canvas->setHighlightedShape(nullptr);
            canvas->redraw();
        } else {
             std::cout << "[DEBUG] ToolbarChange: Left toolbar tool changed." << std::endl;
             if (tool != MOUSE && selectedShape) {
                 selectedShape = nullptr;
                 canvas->setHighlightedShape(nullptr);
                 canvas->redraw();
             }
             currentScribble = nullptr;
        }
        changedToolbar->resetAction();
    }
}


void Application::onColorSelectorChange() {
    std::cout << "[DEBUG] ColorSelectorChange: Handler called." << std::endl;
    Color color = colorSelector->getColor();
    std::cout << "[DEBUG] ColorSelectorChange: Got color R=" << color.getR() << " G=" << color.getG() << " B=" << color.getB() << std::endl;

    if (selectedShape) {
        std::cout << "[DEBUG] ColorSelectorChange: Shape IS selected. Address: " << selectedShape << ". Calling setColor..." << std::endl;
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        std::cout << "[DEBUG] ColorSelectorChange: setColor called. Redrawing canvas..." << std::endl;
        canvas->redraw();
    } else {
         std::cout << "[DEBUG] ColorSelectorChange: Shape IS NOT selected. Doing nothing." << std::endl;
    }
}

void Application::staticColorSelectorCallback(Fl_Widget* w, void* data) {
     std::cout << "[DEBUG] Static callback triggered." << std::endl;
     Application* app_instance = static_cast<Application*>(data);
     if (app_instance) {
         // Call the actual instance member function
         app_instance->onColorSelectorChange();
     } else {
          std::cout << "[DEBUG] Static callback error: User data (app instance) is null!" << std::endl;
     }
}


Application::Application() :
    window(nullptr), toolbar(nullptr), rightToolbar(nullptr),
    canvas(nullptr), colorSelector(nullptr),
    selectedShape(nullptr), currentScribble(nullptr),
    isDraggingShape(false), lastMouseX(0.0f), lastMouseY(0.0f)
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

    // Removed: ON_CHANGE(colorSelector, Application::onColorSelectorChange);
    // Added: Standard FLTK callback registration
    colorSelector->callback(staticColorSelectorCallback, this);

    std::cout << "[DEBUG] Application: Callbacks registered." << std::endl;

    window->show();
}

Application::~Application() {
    delete window;
    std::cout << "[DEBUG] Application destroyed." << std::endl;
}