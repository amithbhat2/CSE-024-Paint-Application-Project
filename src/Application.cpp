#include "Application.h"
#include "Enums.h"

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        startScribble(mx, my, color.getR(), color.getG(), color.getB());
    }
    else if (tool == ERASER) {
        eraseAtPosition(mx, my);
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == CIRCLE) { 
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == TRIANGLE) {
        canvas->addTriangle(mx, my, 0.2, 0.2, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == POLYGON) {
        canvas->addPolygon(mx, my, 5, 0.1, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == FRONT) {
        if (Shape* shape = canvas->getSelectedShape(mx, my)) {
            canvas->bringToFront(shape);
            canvas->redraw();
        }
    }
    else if (tool == BACK) {
        if (Shape* shape = canvas->getSelectedShape(mx, my)) {
            canvas->sendToBack(shape);
            canvas->redraw();
        }
    }
    else if (tool == MOUSE) {
        selectedShape = canvas->getSelectedShape(mx, my);
        if (selectedShape) {
            isDragging = true;
            lastMouseX = mx;
            lastMouseY = my;
        }
    }
}

void Application::onCanvasDrag(Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        continueScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
    }
    else if (tool == ERASER) {
        eraseAtPosition(mx, my);
    }
    else if (tool == MOUSE && isDragging && selectedShape) {
        float dx = mx - lastMouseX;
        float dy = my - lastMouseY;
        selectedShape->move(dx, dy);
        lastMouseX = mx;
        lastMouseY = my;
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    
    if (tool == PENCIL) {
        endScribble();
    }
    isDragging = false;
}

void Application::onToolbarChange(Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
        selectedShape = nullptr;
        canvas->redraw();
    }   
    else if (action == INCREASE && selectedShape) {
        selectedShape->resize(1.1f, 1.1f);
        canvas->redraw();
    }   
    else if (action == DECREASE && selectedShape) {
        selectedShape->resize(0.9f, 0.9f);
        canvas->redraw();
    }
    else if (action == UNDO) {
        canvas->undo();
        canvas->redraw();
    }
}

void Application::onColorSelectorChange(Widget* sender) {
    Color color = colorSelector->getColor();
    if (selectedShape) {
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
}

void Application::startScribble(float x, float y, float r, float g, float b) {
    canvas->startScribble(x, y, Color(r, g, b));
    isDrawingScribble = true;
}

void Application::continueScribble(float x, float y, float r, float g, float b, int size) {
    if (isDrawingScribble) {
        canvas->updateScribble(x, y, r, g, b, size);
        canvas->redraw();
    }
}

void Application::endScribble() {
    if (isDrawingScribble) {
        canvas->endScribble();
        isDrawingScribble = false;
        canvas->redraw();
    }
}

void Application::eraseAtPosition(float mx, float my) {
    Shape* shapeToErase = canvas->getSelectedShape(mx, my);
    if (shapeToErase) {
        canvas->removeShape(shapeToErase);
        if (selectedShape == shapeToErase) {
            selectedShape = nullptr;
        }
        canvas->redraw();
    }
}

Application::Application() {
    window = new Window(25, 75, 650, 650, "Paint App Project");

    selectedShape = nullptr;
    isDragging = false;
    isDrawingScribble = false;
    lastMouseX = 0;
    lastMouseY = 0;

    toolbar = new Toolbar(0, 0, 50, 650);
    canvas = new Canvas(50, 0, 600, 600);
    colorSelector = new ColorSelector(50, 600, 450, 50);
    colorSelector->box(FL_BORDER_BOX);

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