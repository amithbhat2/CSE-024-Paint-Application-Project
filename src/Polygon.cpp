#include "Polygon.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

Polygon::Polygon() {
    x = 0.0;
    y = 0.0;
    size = 0.2;
    sides = 6;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Polygon::Polygon(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    size = 0.2;
    sides = 6; 
    this->r = r;
    this->g = g;
    this->b = b;
}

void Polygon::draw() {
    glColor3f(r, g, b);

    float angle = 2.0 * M_PI / sides;
    
    glBegin(GL_POLYGON);
        for (int i = 0; i < sides; i++) {
            float currentAngle = i * angle;
            glVertex2f(x + size * cos(currentAngle), y + size * sin(currentAngle));
        }
    glEnd();
}

bool Polygon::contains(float mx, float my) {
    float distance = sqrt(pow(mx - x, 2) + pow(my - y, 2));
    
    if (distance <= size) {
        return true;
    }
    
    return false;
}

void Polygon::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Polygon::move(float dx, float dy) {
    x += dx;
    y += dy;
}
