#include "Rectangle.h"
#include <GL/freeglut.h>

Rectangle::Rectangle() {
    x = 0.0;
    y = 0.0;
    width = 0.4;
    height = 0.4;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Rectangle::Rectangle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    width = 0.4;
    height = 0.4;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::draw() {
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
        glVertex2f(x - width/2, y + height/2);
        glVertex2f(x + width/2, y + height/2);
        glVertex2f(x + width/2, y - height/2);
        glVertex2f(x - width/2, y - height/2);
    glEnd();
}

bool Rectangle::contains(float mx, float my) {
    if (mx >= x - width/2 && mx <= x + width/2 && my <= y + height/2 && my >= y - height/2) {
        return true;
    }
    return false;
}

void Rectangle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Rectangle::resize(float scaleFactor) {
    width *= scaleFactor;
    height *= scaleFactor;
    
    // Ensure the rectangle doesn't get too small
    if (width < 0.1) {
        width = 0.1;
    }
    if (height < 0.1) {
        height = 0.1;
    }
}

Shape* Rectangle::clone() const {
    Rectangle* copy = new Rectangle();
    copy->x = this->x;
    copy->y = this->y;
    copy->width = this->width;
    copy->height = this->height;
    copy->r = this->r;
    copy->g = this->g;
    copy->b = this->b;
    return copy;
}