#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
    float x;
    float y;
    float size;
    float r;
    float g;
    float b;

public:
    Triangle();
    Triangle(float x, float y, float r, float g, float b);
    void draw();
    bool contains(float mx, float my);
    void setColor(float r, float g, float b);
    
    void move(float dx, float dy);
};

#endif