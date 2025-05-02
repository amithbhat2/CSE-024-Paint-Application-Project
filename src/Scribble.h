#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include "Point.h"
#include <vector>

class Scribble: public Shape {
    std::vector<Point*> points;
    float r, g, b;
    int size;
    float offsetX, offsetY;  // For moving the scribble

public:
    Scribble(float r, float g, float b, int size);
    
    void addPoint(float x, float y);
    bool contains(float mx, float my);
    void draw();
    void setColor(float r, float g, float b);
    void move(float dx, float dy);
    void resize(float factor);
    
    ~Scribble();
};
#endif