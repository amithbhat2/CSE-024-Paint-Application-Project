#include "Toolbar.h"
#include <FL/Enumerations.H>
using namespace bobcat;

void Toolbar::deselectAllTools() {
    pencilButton->color(FL_BACKGROUND_COLOR);
    eraserButton->color(FL_BACKGROUND_COLOR);
    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
    polygonButton->color(FL_BACKGROUND_COLOR);
    increaseButton->color(FL_BACKGROUND_COLOR);
    decreaseButton->color(FL_BACKGROUND_COLOR);
    frontButton->color(FL_BACKGROUND_COLOR);
    backButton->color(FL_BACKGROUND_COLOR);
    mouseButton->color(FL_BACKGROUND_COLOR);
}

void Toolbar::visualizeSelectedTool() {
    if (tool == PENCIL) {
        pencilButton->color(FL_WHITE);
    }
    else if (tool == ERASER) {
        eraserButton->color(FL_WHITE);
    }
    else if (tool == CIRCLE) {
        circleButton->color(FL_WHITE);
    }
    else if (tool == TRIANGLE) {
        triangleButton->color(FL_WHITE);
    }
    else if (tool == RECTANGLE) {
        rectangleButton->color(FL_WHITE);
    }
    else if (tool == POLYGON) {
        polygonButton->color(FL_WHITE);
    }
    else if (tool == FRONT) {
        frontButton->color(FL_WHITE);
    }
    else if (tool == BACK) {
        backButton->color(FL_WHITE);
    }
    else if (tool == MOUSE) {
        mouseButton->color(FL_WHITE);
    }
}

void Toolbar::onClick(bobcat::Widget* sender) {
    deselectAllTools();

    action = NONE;

    if (sender == pencilButton) {
        tool = PENCIL;
    }
    else if (sender == eraserButton) {
        tool = ERASER;
    }
    else if (sender == circleButton) {
        tool = CIRCLE;
    }
    else if (sender == triangleButton) {
        tool = TRIANGLE;
    }
    else if (sender == rectangleButton) {
        tool = RECTANGLE;
    }
    else if (sender == polygonButton) {
        tool = POLYGON;
    }
    else if (sender == increaseButton) {
        action = INCREASE;
    }
    else if (sender == decreaseButton) {
        action = DECREASE;
    }
    else if (sender == frontButton) {
        tool = FRONT;
    }
    else if (sender == backButton) {
        tool = BACK;
    }
    else if (sender == undoButton) {
        action = UNDO;
    }
    else if (sender == clearButton) {
        action = CLEAR;
    }
    else if (sender == mouseButton) {
        tool = MOUSE;
    }

    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedTool();
    redraw();
}

TOOL Toolbar::getTool() const {
    return tool;
}

ACTION Toolbar::getAction() const {
    return action;
}

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    pencilButton = new Image(x, y, 50, 50, "./assets/pencil.png");
    eraserButton = new Image(x, y + 50, 50, 50, "./assets/eraser.png");
    circleButton = new Image(x, y + 100, 50, 50, "./assets/circle.png");
    triangleButton = new Image(x, y + 150, 50, 50, "./assets/triangle.png");
    rectangleButton = new Image(x, y + 200, 50, 50, "./assets/rectangle.png");
    polygonButton = new Image(x, y + 250, 50, 50, "./assets/polygon.png");
    increaseButton = new Image (x, y + 300, 50, 50, "./assets/plus.png");
    decreaseButton = new Image (x, y + 350, 50, 50, "./assets/minus.png");
    frontButton = new Image (x, y + 400, 50, 50, "./assets/bring-to-front.png");
    backButton = new Image(x, y + 450, 50, 50, "./assets/send-to-back.png");
    undoButton = new Image (x, y + 500, 50, 50, "./assets/undo.png");
    clearButton = new Image(x, y + 550, 50, 50, "./assets/clear.png");
    mouseButton = new Image(x, y + 600, 50, 50, "./assets/mouse.png");

    tool = PENCIL;
    action = NONE;

    pencilButton->box(FL_BORDER_BOX);
    eraserButton->box(FL_BORDER_BOX);
    circleButton->box(FL_BORDER_BOX);
    triangleButton->box(FL_BORDER_BOX);
    rectangleButton->box(FL_BORDER_BOX);
    polygonButton->box(FL_BORDER_BOX);
    increaseButton->box(FL_BORDER_BOX);
    decreaseButton->box(FL_BORDER_BOX);
    frontButton->box(FL_BORDER_BOX);
    backButton->box(FL_BORDER_BOX);
    undoButton->box(FL_BORDER_BOX);
    clearButton->box(FL_BORDER_BOX);
    mouseButton->box(FL_BORDER_BOX);
    

    visualizeSelectedTool();

    ON_CLICK(pencilButton, Toolbar::onClick);
    ON_CLICK(eraserButton, Toolbar::onClick);
    ON_CLICK(circleButton, Toolbar::onClick);
    ON_CLICK(triangleButton, Toolbar::onClick);
    ON_CLICK(rectangleButton, Toolbar::onClick);
    ON_CLICK(polygonButton, Toolbar::onClick);
    ON_CLICK(increaseButton, Toolbar::onClick);
    ON_CLICK(decreaseButton, Toolbar::onClick);
    ON_CLICK(frontButton, Toolbar::onClick);
    ON_CLICK(backButton, Toolbar::onClick);
    ON_CLICK(undoButton, Toolbar::onClick);
    ON_CLICK(clearButton, Toolbar::onClick);
    ON_CLICK(mouseButton, Toolbar::onClick);

}