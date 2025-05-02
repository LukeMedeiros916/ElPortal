#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <bobcat_ui/all.h>
#include "Enums.h"

class Toolbar : public bobcat::Group {
    bobcat::Image* pencilButton;
    bobcat::Image* eraserButton;
    bobcat::Image* circleButton;
    bobcat::Image* triangleButton;
    bobcat::Image* rectangleButton;
    bobcat::Image* polygonButton;
    bobcat::Image* clearButton;
    bobcat::Image* mouseButton;

    bobcat::Image* bringToFrontButton;
    bobcat::Image* sendToBackButton;

    bobcat::Image* plusButton;
    bobcat::Image* minusButton;

    TOOL tool;
    ACTION action;

    void deselectAllTools();
    void visualizeSelectedTool();
    void onClick(bobcat::Widget* sender);
    void onLayerOrderClick(bobcat::Widget* sender);
    void onZoomClick(bobcat::Widget* sender);

public:
    Toolbar(int x, int y, int w, int h, bool createDefaultButtons = true);

    TOOL getTool() const;
    ACTION getAction() const;
    void resetAction();

};

#endif

// Working as of May 3 | ALso beautified code