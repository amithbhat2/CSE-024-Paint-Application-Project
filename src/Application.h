#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorSelector.h"
#include "Enums.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Toolbar* toolbar;
    Canvas* canvas;
    ColorSelector* colorSelector;
    Shape* selectedShape;

    bool isDragging;
    bool isDrawingScribble;
    float lastMouseX;
    float lastMouseY;

    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);
    void onColorSelectorChange(bobcat::Widget* sender);

    void eraseAtPosition(float mx, float my);
    void startScribble(float x, float y, float r, float g, float b);
    void continueScribble(float x, float y, float r, float g, float b, int size);
    void endScribble();

public:
    Application();

    friend struct AppTest;
};

#endif