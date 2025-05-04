#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorSelector.h"
#include "Scribble.h"
#include "Shape.h"
#include <FL/Fl_Widget.H>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Toolbar* toolbar;
    Toolbar* rightToolbar;
    Canvas* canvas;
    ColorSelector* colorSelector;
    Shape* selectedShape;
    Scribble* currentScribble;

    bool isDraggingShape;
    float lastMouseX;
    float lastMouseY;

    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);

    void onColorSelectorChange();

    static void staticColorSelectorCallback(Fl_Widget* w, void* data);

public:
    Application();
    virtual ~Application();

    friend struct ::AppTest;
};

#endif