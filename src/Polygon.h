#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include <vector>

class Polygon : public Shape {
    float x;
    float y;
    float size;
    int sides;
    float r;
    float g;
    float b;

public:
    Polygon();
    Polygon(float x, float y, float r, float g, float b);
    void draw();
    bool contains(float mx, float my);
    void setColor(float r, float g, float b);
    
    // Movement and resizing methods
    void move(float dx, float dy);
    void resize(float factor);
};

#endif