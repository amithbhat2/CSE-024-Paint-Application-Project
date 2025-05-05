#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Shape.h"
#include "Color.h"
#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Scribble.h"
#include "Triangle.h"
#include "Polygon.h"

class Canvas : public bobcat::Canvas_ {
    std::vector<Point*> points;
    std::vector<Shape*> shapes; // Order: [0]=backmost, [size-1]=frontmost
    Shape* selectedShape;
    Scribble* currentScribble;

public:
    Canvas(int x, int y, int w, int h);

    // Shape management
    void addPoint(float x, float y, float r, float g, float b, int size);
    void addRectangle(float x, float y, float r, float g, float b);
    void addCircle(float x, float y, float r, float g, float b);
    void addTriangle(float x, float y, float base, float height, float r, float g, float b);
    void addPolygon(float x, float y, int sides, float length, float r, float g, float b);
    
    // Z-order operations
    void bringToFront(Shape* shape);
    void sendToBack(Shape* shape);
    
    // Selection and modification
    Shape* getSelectedShape(float mx, float my);
    void removeShape(Shape* shape);
    void resizeSelectedShape(Shape* shape, float scaleX, float scaleY);
    
    // Scribble operations
    void startScribble(float startX, float startY, Color color);
    void updateScribble(float x, float y, float r, float g, float b, int size);
    void endScribble();
    
    // Canvas operations
    void undo();
    void clear();
    void render();
    
    // Event handling
    int handle(int event);
};

#endif