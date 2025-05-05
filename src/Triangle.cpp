#include "Triangle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

Triangle::Triangle() {
    x = 0.0;
    y = 0.0;
    base = 0.2;
    height = 0.2;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Triangle::Triangle(float x, float y, float base, float height, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->base = base;
    this->height = height;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
        glVertex2f(x - base/2, y - height/2);
        glVertex2f(x, y + height/2);
        glVertex2f(x + base/2, y - height/2);
    glEnd();
}


bool Triangle::contains(float mx, float my) {
 
    float x1 = x - base / 2.0f;
    float y1 = y - height / 2.0f;

    float x2 = x;
    float y2 = y + height / 2.0f;

    float x3 = x + base / 2.0f;
    float y3 = y - height / 2.0f;

    float denom = ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));

    if (denom == 0.0f) {
        return false;
    }

    float a = ((y2 - y3)*(mx - x3) + (x3 - x2)*(my - y3)) / denom;
    float b = ((y3 - y1)*(mx - x3) + (x1 - x3)*(my - y3)) / denom;
    float c = 1.0f - a - b;

    if (a >= 0 && b >= 0 && c >= 0) {
        return true;
    }

    return false;
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

void Triangle::resize(float scaleX, float scaleY) {
    base *= scaleX;
    height *= scaleY;
}