#pragma once
#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square(Point start, Point end, RGBColor fillColor) : Rectangle(start, end, fillColor) {
        name = "Square in layer " + to_string(layer);
    }

protected:
    virtual void handlePoints() {
        int x1 = start.x();
        int y1 = start.y();
        int x2 = end.x();
        int y2 = end.y();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);
        int side = min(width, height);
        if (x2 < x1)
            side = -side;

        topLeft = Point(x1, y1);
        bottomRight = Point(x1 + side, y1 + side);
        if (side < 0) {
            swap(topLeft, bottomRight);
        }

        specifyPoints();
    }
};