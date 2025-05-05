#include "Scribble.h"
#include <GL/freeglut.h>

Scribble::Scribble(float startX, float startY, float r, float g, float b) {
    points.push_back(new Point(startX, startY, r, g, b, 5));
}

Scribble::~Scribble() {
    for (auto point : points) {
        delete point;
    }
}

void Scribble::addPoint(float x, float y, float r, float g, float b, int size) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Scribble::draw() {
    glBegin(GL_POINTS);
    for (auto point : points) {
        glColor3f(point->getR(), point->getG(), point->getB());
        glPointSize(point->getSize());
        glVertex2f(point->getX(), point->getY());
    }
    glEnd();
}

bool Scribble::contains(float mx, float my) {
    for (auto point : points) {
        float dx = point->getX() - mx;
        float dy = point->getY() - my;
        if (dx*dx + dy*dy < 0.0025f) { // 0.05^2 threshold
            return true;
        }
    }
    return false;
}

void Scribble::setColor(float r, float g, float b) {
    for (auto point : points) {
        point->setColor(r, g, b);
    }
}

void Scribble::move(float dx, float dy) {
    for (auto point : points) {
        point->setX(point->getX() + dx);
        point->setY(point->getY() + dy);
    }
}

void Scribble::resize(float scaleX, float scaleY) {
    for (auto point : points) {
        point->setX(point->getX() * scaleX);
        point->setY(point->getY() * scaleY);
    }
}