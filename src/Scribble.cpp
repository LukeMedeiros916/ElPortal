#include "Scribble.h"
#include <GL/freeglut.h>
#include <cmath>
#include <limits>

Scribble::Scribble(float r, float g, float b, int size) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->size = size;
}

void Scribble::addPoint(float x, float y) {
    points.push_back(Point(x, y));
}

void Scribble::draw() {
    if (points.empty()) {
        return;
    }

    glColor3f(r, g, b);
    glLineWidth((float)size);


    glBegin(GL_LINE_STRIP);
    for (const auto& point : points) {
        glVertex2f(point.getX(), point.getY());
    }
    glEnd();

   
    glPointSize((float)size);
    glBegin(GL_POINTS);
     for (const auto& point : points) {
        glVertex2f(point.getX(), point.getY());
    }
    glEnd();
}


bool Scribble::contains(float mx, float my) {
    if (points.size() < 2) {
        
         if (points.size() == 1) {
            float dx = mx - points[0].getX();
            float dy = my - points[0].getY();
            
            float pointSelectRadius = 0.02f;
            return (dx * dx + dy * dy) < (pointSelectRadius * pointSelectRadius);
         }
        return false;
    }

   
    float tolerance = 0.02f;
    float min_dist_sq = tolerance * tolerance;

    for (size_t i = 0; i < points.size() - 1; ++i) {
        float p1x = points[i].getX();
        float p1y = points[i].getY();
        float p2x = points[i + 1].getX();
        float p2y = points[i + 1].getY();

      
        float len_sq = (p2x - p1x) * (p2x - p1x) + (p2y - p1y) * (p2y - p1y);

        if (len_sq == 0.0f) { 
             float dx = mx - p1x;
             float dy = my - p1y;
             if ((dx * dx + dy * dy) < min_dist_sq) return true;
             continue;
        }

       
        float t = ((mx - p1x) * (p2x - p1x) + (my - p1y) * (p2y - p1y)) / len_sq;
        t = std::max(0.0f, std::min(1.0f, t)); 

        
        float closestX = p1x + t * (p2x - p1x);
        float closestY = p1y + t * (p2y - p1y);

   
        float dx = mx - closestX;
        float dy = my - closestY;
        float dist_sq = dx * dx + dy * dy;

        if (dist_sq < min_dist_sq) {
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

// Working as of May 2