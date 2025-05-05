#include "ColorSelector.h"
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <cmath>
#include <algorithm>
#include <iostream>

void ColorSelector::hsvToRgb(float h, float s, float v, float& r, float& g, float& b) {
     r = v; g = v; b = v;
     if (s > 0.0f) {
        h *= 6.0f;
        int i = static_cast<int>(floor(h));
        float f = h - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));

        switch (i % 6) {
            case 0: r = v; g = t; b = p; break;
            case 1: r = q; g = v; b = p; break;
            case 2: r = p; g = v; b = t; break;
            case 3: r = p; g = q; b = v; break;
            case 4: r = t; g = p; b = v; break;
            case 5: r = v; g = p; b = q; break;
        }
    }
}

Color ColorSelector::getColorAtX(float localX) {
    float saturation = 1.0f;
    float value = 1.0f;
    float hue = std::max(0.0f, std::min(1.0f, localX / (w() > 0 ? static_cast<float>(w()) : 1.0f)));
    float r, g, b;
    hsvToRgb(hue, saturation, value, r, g, b);
    return Color(r, g, b);
}

ColorSelector::ColorSelector(int x, int y, int w, int h, const char* label)
    : bobcat::Group(x, y, w, h, label) {
    box(FL_FLAT_BOX);
    selectorX = static_cast<float>(w) / 2.0f;
    selectedColor = getColorAtX(selectorX);
    dragging = false;
}


Color ColorSelector::getColor() const {
    return selectedColor;
}


void ColorSelector::draw() {

    if (damage() & FL_DAMAGE_ALL) {
        fl_push_clip(x(), y(), w(), h());

        for (int i = 0; i < w(); ++i) {
            Color col = getColorAtX(static_cast<float>(i));
            fl_color(fl_rgb_color(static_cast<uchar>(col.getR() * 255),
                                 static_cast<uchar>(col.getG() * 255),
                                 static_cast<uchar>(col.getB() * 255)));
            fl_line(x() + i, y(), x() + i, y() + h() - 1);
        }

        fl_pop_clip();
    }


    fl_push_clip(x(), y(), w(), h());
    int drawX = x() + static_cast<int>(selectorX);
    int circleRadius = h() / 4;
    int circleY = y() + h() / 2;


    fl_color(FL_BLACK);
    fl_arc(drawX - circleRadius, circleY - circleRadius, circleRadius * 2, circleRadius * 2, 0, 360);


    Color scol = getColor();
    fl_color(fl_rgb_color(static_cast<uchar>(scol.getR() * 255),
                             static_cast<uchar>(scol.getG() * 255),
                             static_cast<uchar>(scol.getB() * 255)));
    fl_pie(drawX - circleRadius + 2, circleY - circleRadius + 2, (circleRadius - 2) * 2, (circleRadius - 2) * 2, 0, 360);


    fl_pop_clip();

}


int ColorSelector::handle(int event) {
    int result = 0;
    float currentEventX = static_cast<float>(Fl::event_x());

    switch (event) {
        case FL_PUSH:
            if (Fl::event_inside(this)) {
                dragging = true;
                float newSelectorX = std::max(0.0f, std::min(static_cast<float>(w()), currentEventX - x()));
                if (std::abs(newSelectorX - selectorX) > 1e-6) {
                    selectorX = newSelectorX;
                    Color newColor = getColorAtX(selectorX);
                    if (newColor.getR() != selectedColor.getR() ||
                        newColor.getG() != selectedColor.getG() ||
                        newColor.getB() != selectedColor.getB())
                    {
                        selectedColor = newColor;
                        std::cout << "[DEBUG] ColorSelector::handle(FL_PUSH): Color changed. Calling do_callback()." << std::endl;
                        do_callback();
                    }
                    redraw();
                }
                result = 1;
            }
            break;

        case FL_DRAG:
            if (dragging) {
                float newSelectorX = std::max(0.0f, std::min(static_cast<float>(w()), currentEventX - x()));
                 if (std::abs(newSelectorX - selectorX) > 1e-6) { // Check if position actually changed
                    selectorX = newSelectorX;
                    Color newColor = getColorAtX(selectorX);
                    if (newColor.getR() != selectedColor.getR() ||
                        newColor.getG() != selectedColor.getG() ||
                        newColor.getB() != selectedColor.getB())
                    {
                        selectedColor = newColor;
                        std::cout << "[DEBUG] ColorSelector::handle(FL_DRAG): Color changed. Calling do_callback()." << std::endl;
                        do_callback();
                    }
                    redraw();
                 }
                result = 1;
            }
            break;

        case FL_RELEASE:
            if (dragging) {
                dragging = false;
                result = 1;
            }
            break;


        default:
            result = bobcat::Group::handle(event);
            break;
    }
    return result;
}
// Used https://codebeautify.org/ to keep code readable and nice