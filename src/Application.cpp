#include "Application.h"
#include "Enums.h"

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        // Start a new scribble
        canvas->startScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        // Erase any shape at the current position
        canvas->eraseAt(mx, my);
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
    else if (tool == TRIANGLE) {
        canvas->addTriangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == POLYGON) {
        canvas->addPolygon(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == MOUSE) {
        selectedShape = canvas->getSelectedShape(mx, my);
        
        if (selectedShape) {
            isDragging = true;
            lastMouseX = mx;
            lastMouseY = my;
            
            canvas->take_focus();
        }
    }
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        // Update the current scribble with a new point
        canvas->updateScribble(mx, my);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        // Continue erasing shapes as the mouse is dragged
        canvas->eraseAt(mx, my);
        canvas->redraw();
    }
    else if (tool == MOUSE && isDragging && selectedShape) {
        // Calculate the movement delta
        float dx = mx - lastMouseX;
        float dy = my - lastMouseY;
        
        // Move the shape
        selectedShape->move(dx, dy);
        
        // Update the last mouse position
        lastMouseX = mx;
        lastMouseY = my;
        
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    
    if (tool == PENCIL) {
        // Finish and save the current scribble
        canvas->endScribble();
    }
    
    isDragging = false;
}

void Application::onKeyDown(bobcat::Widget* sender, int key) {
    if (key == FL_Control_L + 'z' || key == FL_Control_L + 'Z') {
        // Handle Ctrl+Z for undo
        canvas->undo();
        canvas->redraw();
    }
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
        selectedShape = nullptr;
        canvas->redraw();
    }
    else if (action == FRONT && selectedShape) {
        canvas->bringToFront(selectedShape);
        canvas->redraw();
    }
    else if (action == BACK && selectedShape) {
        canvas->sendToBack(selectedShape);
        canvas->redraw();
    }
    else if (action == UNDO) {
        canvas->undo();
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
    window = new Window(25, 75, 400, 400, "Paint Application");

    selectedShape = nullptr;
    isDragging = false;
    lastMouseX = 0;
    lastMouseY = 0;

    toolbar = new Toolbar(0, 0, 50, 400);
    canvas = new Canvas(50, 0, 350, 350);
    colorSelector = new ColorSelector(50, 350, 350, 50);
    colorSelector->box(FL_BORDER_BOX);

    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_KEY_DOWN(canvas, Application::onKeyDown);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(colorSelector, Application::onColorSelectorChange);
    
    canvas->take_focus();

    window->show();
}