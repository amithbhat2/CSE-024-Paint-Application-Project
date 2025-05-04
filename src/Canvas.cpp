#include "Canvas.h"
#include "Enums.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Scribble.h"
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

    auto it = std::find(shapes.begin(), shapes.end(), shape);
    if (it != shapes.end()) {

        shapes.erase(it);

        shapes.push_back(shape);
    }
}

void Canvas::sendToBack(Shape* shape) {

    auto it = std::find(shapes.begin(), shapes.end(), shape);
    if (it != shapes.end()) {

        shapes.erase(it);

        shapes.insert(shapes.begin(), shape);
    }
}

void Canvas::undo(){
    if (shapes.size() > 0){
        delete shapes[shapes.size() - 1];
        shapes.pop_back();
    }
}

int Canvas::handle(int event) {
    int ret = Canvas_::handle(event);
    return ret; 
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