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
    currentScribble = nullptr;
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

void Canvas::addTriangle(float x, float y, float base, float height, float r, float g, float b) {
    shapes.push_back(new Triangle(x, y, base, height, r, g, b));
}

void Canvas::addPolygon(float x, float y, int sides, float length, float r, float g, float b) {
    shapes.push_back(new Polygon(x, y, sides, length, r, g, b));
}

void Canvas::removeShape(Shape* shape) {
    auto it = std::find(shapes.begin(), shapes.end(), shape);
    if (it != shapes.end()) {
        if (selectedShape == *it) {
            selectedShape = nullptr;
        }
        delete *it; 
        shapes.erase(it);
    }
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

void Canvas::undo() {
    if (!shapes.empty()) {
        delete shapes.back();
        shapes.pop_back();
    }
}

int Canvas::handle(int event) {
    return Canvas_::handle(event);
}

void Canvas::clear() {
    for (auto point : points) {
        delete point;
    }
    points.clear();
    
    for (auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
    
    selectedShape = nullptr;
}

void Canvas::render() {
    for (auto point : points) {
        point->draw();
    }
    
    for (auto shape : shapes) {
        shape->draw();
    }
}

void Canvas::startScribble(float startX, float startY, Color color) {
    currentScribble = new Scribble(startX, startY, color.getR(), color.getG(), color.getB());
}

void Canvas::updateScribble(float x, float y, float r, float g, float b, int size) {
    if (currentScribble) {
        currentScribble->addPoint(x, y, r, g, b, size);
    }
}

void Canvas::endScribble() {
    if (currentScribble) {
        shapes.push_back(currentScribble);
        currentScribble = nullptr;
    }
}


Shape* Canvas::getSelectedShape(float mx, float my) {
    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
        if ((*it)->contains(mx, my)) {
            selectedShape = *it;
            return *it;
        }
    }
    selectedShape = nullptr;
    return nullptr;
}
