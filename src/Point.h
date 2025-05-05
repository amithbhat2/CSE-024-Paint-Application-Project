#ifndef POINT_H
#define POINT_H

class Point {
    float x;
    float y;
    float r;
    float g;
    float b;
    int size;

public:
    Point();
    Point(float x, float y);
    Point(float x, float y, float r, float g, float b);
    Point(float x, float y, float r, float g, float b, int size);

    void draw() const;

    // Getters
    float getX() const;
    float getY() const;
    float getR() const;
    float getG() const;
    float getB() const;
    int getSize() const;

    // Add these simple setters:
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void setSize(int size) { this->size = size; }

    void setColor(float r, float g, float b);
};

#endif