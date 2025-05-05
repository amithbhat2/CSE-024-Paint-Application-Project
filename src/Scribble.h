#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include "Point.h"
#include <vector>

class Scribble : public Shape {
    std::vector<Point*> points;
    
public:
    Scribble(float startX, float startY, float r, float g, float b);
    ~Scribble();
    
    void addPoint(float x, float y, float r, float g, float b, int size);
    
    // Implement all pure virtual methods from Shape
    void draw() override;
    bool contains(float mx, float my) override;
    void setColor(float r, float g, float b) override;
    void move(float dx, float dy) override;
    void resize(float scaleX, float scaleY) override;
};

#endif