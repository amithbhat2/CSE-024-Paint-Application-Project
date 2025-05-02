#include "Scribble.h"
#include <cmath>
#include <limits>

Scribble::Scribble(float r, float g, float b, int size) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->size = size;
    this->offsetX = 0.0f;
    this->offsetY = 0.0f;
}

void Scribble::addPoint(float x, float y) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Scribble::draw() {
    for (unsigned int i = 0; i < points.size(); i++) {
        // Apply the offset to each point's position without modifying the original coordinates
        float origX = points[i]->getX();
        float origY = points[i]->getY();
        
        glColor3f(points[i]->getR(), points[i]->getG(), points[i]->getB());
        glPointSize(points[i]->getSize());
        
        glBegin(GL_POINTS);
        glVertex2f(origX + offsetX, origY + offsetY);
        glEnd();
    }
}

bool Scribble::contains(float mx, float my) {
    // Check if any point in the scribble is close to the mouse position
    const float threshold = 0.02f; // Adjust this value as needed
    
    for (unsigned int i = 0; i < points.size(); i++) {
        float pointX = points[i]->getX() + offsetX;
        float pointY = points[i]->getY() + offsetY;
        
        float distance = sqrt(pow(mx - pointX, 2) + pow(my - pointY, 2));
        if (distance <= threshold) {
            return true;
        }
    }
    
    return false;
}

void Scribble::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
    
    // Update all points to the new color
    for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->setColor(r, g, b);
    }
}

void Scribble::move(float dx, float dy) {
    // Instead of modifying each point's position, we store the offset
    offsetX += dx;
    offsetY += dy;
}

void Scribble::resize(float factor) {
    // Calculate the center of the scribble
    float centerX = 0.0f;
    float centerY = 0.0f;
    
    for (unsigned int i = 0; i < points.size(); i++) {
        centerX += points[i]->getX();
        centerY += points[i]->getY();
    }
    
    if (!points.empty()) {
        centerX /= points.size();
        centerY /= points.size();
    }
    
    // Resize points around the center
    for (unsigned int i = 0; i < points.size(); i++) {
        float dx = points[i]->getX() - centerX;
        float dy = points[i]->getY() - centerY;
        
        float newX = centerX + dx * factor;
        float newY = centerY + dy * factor;
        
        points[i]->setX(newX);
        points[i]->setY(newY);
    }
    
    // Also adjust the point size
    for (unsigned int i = 0; i < points.size(); i++) {
        int newSize = static_cast<int>(points[i]->getSize() * factor);
        if (newSize < 1) newSize = 1;
        points[i]->setSize(newSize);
    }
}

Scribble::~Scribble() {
    for (unsigned int i = 0; i < points.size(); i++) {
        delete points[i];
    }
    points.clear();
}