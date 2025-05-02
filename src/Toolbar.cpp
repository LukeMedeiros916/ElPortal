#include "Toolbar.h"
#include <iostream>
#include <FL/fl_draw.H>

using namespace bobcat;
void Toolbar::deselectAllTools() {
    if (pencilButton) pencilButton->color(FL_BACKGROUND_COLOR);
    if (eraserButton) eraserButton->color(FL_BACKGROUND_COLOR);
    if (circleButton) circleButton->color(FL_BACKGROUND_COLOR);
    if (triangleButton) triangleButton->color(FL_BACKGROUND_COLOR);
    if (rectangleButton) rectangleButton->color(FL_BACKGROUND_COLOR);
    if (polygonButton) polygonButton->color(FL_BACKGROUND_COLOR);
    if (mouseButton) mouseButton->color(FL_BACKGROUND_COLOR);
}

void Toolbar::visualizeSelectedTool() {
    
    if (tool == PENCIL && pencilButton) {
        pencilButton->color(FL_WHITE);
    }
    else if (tool == ERASER && eraserButton) {
        eraserButton->color(FL_WHITE);
    }
    else if (tool == CIRCLE && circleButton) {
        circleButton->color(FL_WHITE);
    }
    else if (tool == TRIANGLE && triangleButton) {
        triangleButton->color(FL_WHITE);
    }
    else if (tool == RECTANGLE && rectangleButton) {
        rectangleButton->color(FL_WHITE);
    }
    else if (tool == POLYGON && polygonButton) {
        polygonButton->color(FL_WHITE);
    }
    else if (tool == MOUSE && mouseButton) {
        mouseButton->color(FL_WHITE);
    }
    
}


void Toolbar::onClick(bobcat::Widget* sender) {
    deselectAllTools();
    action = NONE;

    if (sender == pencilButton) tool = PENCIL;
    else if (sender == eraserButton) tool = ERASER;
    else if (sender == circleButton) tool = CIRCLE;
    else if (sender == triangleButton) tool = TRIANGLE;
    else if (sender == rectangleButton) tool = RECTANGLE;
    else if (sender == polygonButton) tool = POLYGON;
    else if (sender == clearButton) action = CLEAR;
    else if (sender == mouseButton) tool = MOUSE;

    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedTool();
    redraw();
}

void Toolbar::onLayerOrderClick(bobcat::Widget* sender) {
    if (sender == bringToFrontButton) {
        action = BRING_FRONT;
        std::cout << "Toolbar: Set action BRING_FRONT" << std::endl;
    } else if (sender == sendToBackButton) {
        action = SEND_BACK;
        std::cout << "Toolbar: Set action SEND_BACK" << std::endl;
    } else {
        action = NONE;
    }

    if (onChangeCb) {
        onChangeCb(this);
    }
}

TOOL Toolbar::getTool() const { return tool; }
ACTION Toolbar::getAction() const { return action; }

Toolbar::Toolbar(int x_pos, int y_pos, int w, int h, bool createDefaultButtons /*= true*/)
    : Group(x_pos, y_pos, w, h)
{
    pencilButton = nullptr; eraserButton = nullptr; circleButton = nullptr;
    triangleButton = nullptr; rectangleButton = nullptr; polygonButton = nullptr;
    clearButton = nullptr; mouseButton = nullptr; bringToFrontButton = nullptr;
    sendToBackButton = nullptr;

    tool = PENCIL;
    action = NONE;

    if (createDefaultButtons) {
        pencilButton = new Image(x_pos, y_pos, 50, 50, "./assets/pencil.png");
        eraserButton = new Image(x_pos, y_pos + 50, 50, 50, "./assets/eraser.png");
        circleButton = new Image(x_pos, y_pos + 100, 50, 50, "./assets/circle.png");
        triangleButton = new Image(x_pos, y_pos + 150, 50, 50, "./assets/triangle.png");
        rectangleButton = new Image(x_pos, y_pos + 200, 50, 50, "./assets/rectangle.png");
        polygonButton = new Image(x_pos, y_pos + 250, 50, 50, "./assets/polygon.png");
        clearButton = new Image(x_pos, y_pos + 300, 50, 50, "./assets/clear.png");
        mouseButton = new Image(x_pos, y_pos + 350, 50, 50, "./assets/mouse.png");

        pencilButton->box(FL_BORDER_BOX); eraserButton->box(FL_BORDER_BOX);
        circleButton->box(FL_BORDER_BOX); triangleButton->box(FL_BORDER_BOX);
        rectangleButton->box(FL_BORDER_BOX); polygonButton->box(FL_BORDER_BOX);
        clearButton->box(FL_BORDER_BOX); mouseButton->box(FL_BORDER_BOX);

        visualizeSelectedTool();

        ON_CLICK(pencilButton, Toolbar::onClick); ON_CLICK(eraserButton, Toolbar::onClick);
        ON_CLICK(circleButton, Toolbar::onClick); ON_CLICK(triangleButton, Toolbar::onClick);
        ON_CLICK(rectangleButton, Toolbar::onClick); ON_CLICK(polygonButton, Toolbar::onClick);
        ON_CLICK(clearButton, Toolbar::onClick); ON_CLICK(mouseButton, Toolbar::onClick);

    } else {
        box(FL_FLAT_BOX);
        
        color(fl_rgb_color(200, 200, 200));

        bringToFrontButton = new Image(x_pos, y_pos, 50, 50, "./assets/bring-to-front.png");
        sendToBackButton = new Image(x_pos, y_pos + 50, 50, 50, "./assets/send-to-back.png");

        bringToFrontButton->box(FL_BORDER_BOX);
        sendToBackButton->box(FL_BORDER_BOX);

        ON_CLICK(bringToFrontButton, Toolbar::onLayerOrderClick);
        ON_CLICK(sendToBackButton, Toolbar::onLayerOrderClick);
    }
   
}


void Toolbar::resetAction() {
    if (action == BRING_FRONT || action == SEND_BACK || action == CLEAR) {
         std::cout << "Toolbar: Resetting action" << std::endl;
         action = NONE;
    }
}

// Working as of May 2