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

    TOOL tool;
    ACTION action;

    void deselectAllTools();
    void visualizeSelectedTool();
    void onClick(bobcat::Widget* sender); // For tool buttons
    void onLayerOrderClick(bobcat::Widget* sender); // For layer buttons

public:
    Toolbar(int x, int y, int w, int h, bool createDefaultButtons = true);

    TOOL getTool() const;
    ACTION getAction() const;

    void resetAction();

};

#endif