#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Shape.h"
#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Shape.h"

class Canvas : public bobcat::Canvas_ {
    std::vector<Point*> points;
    std::vector<Shape*> shapes;
    Shape* selectedShape;

public:
    Canvas(int x, int y, int w, int h);

    int handle(int event);

    void addPoint(float x, float y, float r, float g, float b, int size);

    void addRectangle(float x, float y, float r, float g, float b);

    void addCircle(float x, float y, float r, float g, float b);

    void addTriangle(float x, float y, float r, float g, float b);

    void addPolygon(float x, float y, float r, float g, float b);
    
    void bringToFront(Shape* shape);
    
    void sendToBack(Shape* shape);

    void clear();

    void render();

    Shape* getSelectedShape(float mx, float my);
};

#endif