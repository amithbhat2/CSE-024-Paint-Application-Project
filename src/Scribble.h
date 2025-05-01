#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include <vector>
#include "Point.h"

class Scribble : public Shape {
    std::vector<Point> points;
    float r;
    float g;
    float b;
    int size;
    float minX, maxX, minY, maxY; // Bounding box

public:
    Scribble(float r, float g, float b, int size);
    
    // Add a point to the scribble
    void addPoint(float x, float y);
    
    // Shape interface implementation
    void draw() override;
    bool contains(float mx, float my) override;
    void setColor(float r, float g, float b) override;
    
    // Movement and resizing methods
    void move(float dx, float dy) override;
    void resize(float factor) override;
    
    // Returns the center point of the scribble for reference
    void getCenter(float& cx, float& cy);
    
private:
    void updateBounds();
};

#endif