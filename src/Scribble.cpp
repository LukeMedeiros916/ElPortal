#include "Scribble.h"
#include <GL/freeglut.h>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

Scribble::Scribble(float r, float g, float b, int size) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->size = std::max(1, size);
}

void Scribble::addPoint(float x, float y) {
    points.push_back(Point(x, y));
}

void Scribble::draw() {
    if (points.empty()) {
        return;
    }

    glColor3f(r, g, b);
    glLineWidth(static_cast<float>(size));

    glBegin(GL_LINE_STRIP);
    for (const auto& point : points) {
        glVertex2f(point.getX(), point.getY());
    }
    glEnd();
}


bool Scribble::contains(float mx, float my) {
    if (points.empty()) {
        return false;
    }

    float line_select_tolerance = 0.02f;
    float point_select_radius = 0.02f;

    if (points.size() == 1) {
        float dx = mx - points[0].getX();
        float dy = my - points[0].getY();
        return (dx * dx + dy * dy) < (point_select_radius * point_select_radius);
    }

    float min_dist_sq = line_select_tolerance * line_select_tolerance;

    for (size_t i = 0; i < points.size() - 1; ++i) {
        float p1x = points[i].getX();
        float p1y = points[i].getY();
        float p2x = points[i + 1].getX();
        float p2y = points[i + 1].getY();

        float seg_vx = p2x - p1x;
        float seg_vy = p2y - p1y;

        float len_sq = seg_vx * seg_vx + seg_vy * seg_vy;

        if (len_sq < 1e-9) {
             float dx = mx - p1x;
             float dy = my - p1y;
             if ((dx * dx + dy * dy) < min_dist_sq) return true;
             continue;
        }

        float t = ((mx - p1x) * seg_vx + (my - p1y) * seg_vy) / len_sq;

        t = std::max(0.0f, std::min(1.0f, t));

        float closestX = p1x + t * seg_vx;
        float closestY = p1y + t * seg_vy;

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

void Scribble::resize(float factor) {
    const int minSize = 1;
    float newFloatSize = static_cast<float>(size) * factor;
    size = std::max(minSize, static_cast<int>(round(newFloatSize)));
}

// Working as of May 3 | ALso beautified code