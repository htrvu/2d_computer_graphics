#pragma once
#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square(Point start, Point end, RGBColor fillColor) : Rectangle(start, end, fillColor) {
        name = "Square in layer " + to_string(layer);
    }

protected:
    virtual void specifyBoundingBox() {
        topLeft = start;
        bottomRight = end;
        squareAdjust(topLeft, bottomRight);
        specifyVertices();
    }
};