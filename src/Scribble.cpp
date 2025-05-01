#include "Scribble.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <algorithm>
#include <cfloat>
#include <cmath>

Scribble::Scribble(float r, float g, float b, int size) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->size = size;
    this->minX = FLT_MAX;
    this->maxX = -FLT_MAX;
    this->minY = FLT_MAX;
    this->maxY = -FLT_MAX;
}

void Scribble::addPoint(float x, float y) {
    points.push_back(Point(x, y, r, g, b, size));
    
    // Update bounds
    minX = std::min(minX, x);
    maxX = std::max(maxX, x);
    minY = std::min(minY, y);
    maxY = std::max(maxY, y);
}

void Scribble::updateBounds() {
    if (points.empty()) return;
    
    minX = FLT_MAX;
    maxX = -FLT_MAX;
    minY = FLT_MAX;
    maxY = -FLT_MAX;
    
    for (const auto& point : points) {
        minX = std::min(minX, point.getX());
        maxX = std::max(maxX, point.getX());
        minY = std::min(minY, point.getY());
        maxY = std::max(maxY, point.getY());
    }
}

void Scribble::draw() {
    glColor3f(r, g, b);
    glPointSize(size);
    
    glBegin(GL_POINTS);
    for (const auto& point : points) {
        glVertex2f(point.getX(), point.getY());
    }
    glEnd();
    
    // Draw lines to connect points
    if (points.size() > 1) {
        glBegin(GL_LINE_STRIP);
        for (const auto& point : points) {
            glVertex2f(point.getX(), point.getY());
        }
        glEnd();
    }
}

bool Scribble::contains(float mx, float my) {
    // Check if point is in bounding box first (quick check)
    if (mx < minX || mx > maxX || my < minY || my > maxY) {
        return false;
    }
    
    // Check distance to each line segment
    const float THRESHOLD = size / 2.0f;
    
    for (size_t i = 1; i < points.size(); i++) {
        float x1 = points[i-1].getX();
        float y1 = points[i-1].getY();
        float x2 = points[i].getX();
        float y2 = points[i].getY();
        
        // Vector from line point 1 to point 2
        float dx = x2 - x1;
        float dy = y2 - y1;
        
        // Length of line segment squared
        float lengthSquared = dx*dx + dy*dy;
        
        if (lengthSquared == 0) continue; // Skip zero-length segments
        
        // Calculate projection of point onto line
        float t = ((mx - x1) * dx + (my - y1) * dy) / lengthSquared;
        t = std::max(0.0f, std::min(1.0f, t)); // Clamp to segment
        
        // Calculate closest point on line
        float projX = x1 + t * dx;
        float projY = y1 + t * dy;
        
        // Distance from point to line
        float distance = std::sqrt((mx - projX)*(mx - projX) + (my - projY)*(my - projY));
        
        if (distance <= THRESHOLD) {
            return true;
        }
    }
    
    return false;
}

void Scribble::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Scribble::move(float dx, float dy) {
    for (auto& point : points) {
        float x = point.getX() + dx;
        float y = point.getY() + dy;
        point = Point(x, y, r, g, b, size);
    }
    
    // Update bounds
    minX += dx;
    maxX += dx;
    minY += dy;
    maxY += dy;
}

void Scribble::resize(float factor) {
    if (points.empty()) return;
    
    // Get center point
    float cx = (minX + maxX) / 2;
    float cy = (minY + maxY) / 2;
    
    // Resize all points relative to center
    for (auto& point : points) {
        float x = point.getX();
        float y = point.getY();
        
        // Vector from center to point
        float vx = x - cx;
        float vy = y - cy;
        
        // Scale the vector
        vx *= factor;
        vy *= factor;
        
        // New position
        point = Point(cx + vx, cy + vy, r, g, b, size);
    }
    
    // Update bounds
    updateBounds();
}

void Scribble::getCenter(float& cx, float& cy) {
    cx = (minX + maxX) / 2;
    cy = (minY + maxY) / 2;
}