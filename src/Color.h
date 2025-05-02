#ifndef COLOR_H
#define COLOR_H

class Color {
    float r;
    float g;
    float b;

public:
    Color();
    Color(float r, float g, float b);

    float getR() const;
    float getG() const;
    float getB() const;

    void setR(float r);
    void setG(float g);
    void setB(float b);
};

#endif

// Working as of May 2