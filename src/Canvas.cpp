#include "Canvas.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Polygon.h"
#include <iostream>
#include <algorithm>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    selectedShape = nullptr;
}

void Canvas::addPoint(float x, float y, float r, float g, float b, int size) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Rectangle(x, y, r, g, b));
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Circle(x, y, r, g, b));
}

void Canvas::addTriangle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Triangle(x, y, r, g, b));
}

void Canvas::addPolygon(float x, float y, float r, float g, float b) {
    shapes.push_back(new Polygon(x, y, r, g, b));
}

void Canvas::bringToFront(Shape* shape) {
    // Find shape in the vector
    auto it = std::find(shapes.begin(), shapes.end(), shape);
    if (it != shapes.end()) {
        // Remove from current position
        shapes.erase(it);
        // Add to end (front of drawing order)
        shapes.push_back(shape);
    }
}

void Canvas::sendToBack(Shape* shape) {
    // Find shape in the vector
    auto it = std::find(shapes.begin(), shapes.end(), shape);
    if (it != shapes.end()) {
        // Remove from current position
        shapes.erase(it);
        // Add to beginning (back of drawing order)
        shapes.insert(shapes.begin(), shape);
    }
}

int Canvas::handle(int event) {
    // Call the base class handle method
    int ret = Canvas_::handle(event);

    // Process keyboard events
    if (event == FL_KEYDOWN && selectedShape != nullptr) {
        int key = Fl::event_key();

        // Resize with + and - keys
        if (key == '+' || key == '=') {
            selectedShape->resize(1.1); // Increase size by 10%
            redraw();
            return 1; // Event was handled
        } else if (key == '-' || key == '_') {
            selectedShape->resize(0.9); // Decrease size by 10%
            redraw();
            return 1; // Event was handled
        }
        // Bring to front with F key
        else if (key == 'f' || key == 'F') {
            bringToFront(selectedShape);
            redraw();
            return 1; // Event was handled
        }
        // Send to back with B key
        else if (key == 'b' || key == 'B') {
            sendToBack(selectedShape);
            redraw();
            return 1; // Event was handled
        }
    }
    return ret; // Return the base class result
}

void Canvas::clear() {
    for (unsigned int i = 0 ; i < points.size(); i++) {
        delete points[i];
    }
    points.clear();
    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();
}

void Canvas::render() {
    for (unsigned int i = 0 ; i < points.size(); i++) {
        points[i]->draw();
    }
    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
}

Shape* Canvas::getSelectedShape(float mx, float my) {
    Shape* result = nullptr;

    // Iterate in reverse order to get the top-most shape first
    for (int i = shapes.size() - 1; i >= 0; i--) {
        // ask every shape if we clicked on it
        if (shapes[i]->contains(mx, my)) {
            std::cout << "Clicked on shape[" << i << "]" << std::endl;
            result = shapes[i];
            selectedShape = result; // Keep track of selected shape in Canvas
            break;
        }
    }
    if (result == nullptr) {
        std::cout << "No selected shape" << std::endl;
        selectedShape = nullptr; // Clear selection
    }
    return result;
}