#include "Polygon.h"
#include <GL/freeglut.h>
#include <cmath>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Polygon::calculateVertices() {
    vertices_x.clear();
    vertices_y.clear();
    float angle_offset = M_PI / 2.0f;
    float angle_increment = 2.0f * M_PI / sides;

    for (int i = 0; i < sides; ++i) {
        float angle = i * angle_increment + angle_offset;
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
    sides = n_sides > 2 ? n_sides : 3;
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

        if (cross_product < 0) {
            all_positive = false;
        }
        if (cross_product > 0) {
            all_negative = false;
        }

    }


    return all_positive || all_negative;
}


void Polygon::setColor(float r_in, float g_in, float b_in) {
    r = r_in;
    g = g_in;
    b = b_in;
}