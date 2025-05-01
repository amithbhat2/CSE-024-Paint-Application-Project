#include "Triangle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

Triangle::Triangle() {
    x = 0.0;
    y = 0.0;
    size = 0.3;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Triangle::Triangle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    size = 0.3;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::draw() {
    glColor3f(r, g, b);

    // Draw an equilateral triangle
    glBegin(GL_TRIANGLES);
        // Top vertex
        glVertex2f(x, y + size/2);
        // Bottom left vertex
        glVertex2f(x - size/2, y - size/2);
        // Bottom right vertex
        glVertex2f(x + size/2, y - size/2);
    glEnd();
}

bool Triangle::contains(float mx, float my) {
    // Define the three vertices of the triangle
    float x1 = x;
    float y1 = y + size/2;
    float x2 = x - size/2;
    float y2 = y - size/2;
    float x3 = x + size/2;
    float y3 = y - size/2;
    
    // Calculate barycentric coordinates
    float denominator = ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
    float a = ((y2 - y3) * (mx - x3) + (x3 - x2) * (my - y3)) / denominator;
    float b = ((y3 - y1) * (mx - x3) + (x1 - x3) * (my - y3)) / denominator;
    float c = 1 - a - b;
    
    // If all barycentric coordinates are between 0 and 1, the point is inside the triangle
    return (a >= 0) && (a <= 1) && (b >= 0) && (b <= 1) && (c >= 0) && (c <= 1);
}

void Triangle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Triangle::resize(float factor) {
    size *= factor;
}
