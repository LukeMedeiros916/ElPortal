#include "Polygon.h"
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <algorithm>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Polygon::calculateVertices() {
    vertices_x.clear();
    vertices_y.clear();
    vertices_x.reserve(sides);
    vertices_y.reserve(sides);

    float angle_increment = 2.0f * M_PI / sides;
    float start_angle = M_PI / 2.0f;

    for (int i = 0; i < sides; ++i) {
        float angle = start_angle + i * angle_increment;
        vertices_x.push_back(x + radius * cos(angle));
        vertices_y.push_back(y + radius * sin(angle));
    }
}

Polygon::Polygon(float cx, float cy, float r_in, float g_in, float b_in, int n_sides) {
    x = cx;
    y = cy;
    r = r_in;
    g = g_in;
    b = b_in;
    radius = 0.2f;
    sides = n_sides >= 3 ? n_sides : 3;
    calculateVertices();
}

void Polygon::draw() {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; ++i) {
        glVertex2f(vertices_x[i], vertices_y[i]);
    }
    glEnd();
}

bool Polygon::contains(float mx, float my) {
    if (sides < 3 || vertices_x.empty()) {
        return false;
    }


    bool all_positive = true;
    bool all_negative = true;

    for (int i = 0; i < sides; ++i) {
        float x1 = vertices_x[i];
        float y1 = vertices_y[i];
        float x2 = vertices_x[(i + 1) % sides];
        float y2 = vertices_y[(i + 1) % sides];
        float cross_product = (x2 - x1) * (my - y1) - (y2 - y1) * (mx - x1);

        const float tolerance = -1e-6;
        if (cross_product < tolerance) {
            all_positive = false;
            break;
        }
    }

    return all_positive;
}


void Polygon::setColor(float r_in, float g_in, float b_in) {
    r = r_in;
    g = g_in;
    b = b_in;
}

void Polygon::resize(float factor) {
    const float minRadius = 0.01f;
    radius = std::max(minRadius, radius * factor);
    calculateVertices();
}

// Working as of May 3 | ALso beautified code