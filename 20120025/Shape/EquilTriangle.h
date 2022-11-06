#pragma once
#include "Triangle.h"

class EquilTriangle : public Triangle {
public:
    EquilTriangle(Point start, Point end, RGBColor fillColor) : Triangle(start, end, fillColor) {
        name = "Equilateral Triangle in layer " + to_string(layer);
    }

protected:
    virtual void specifyPoints() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int side = min(abs(x1 - x2), abs(y1 - y2));
        
        x2 = x1 + side;
        int x3 = (x1 + x2) / 2;
        int y3 = round((float)(side) * sqrt(3) / 2 + y1);
        
        points.push_back(Point(x2, y3));
        points.push_back(Point(x3, y1));
        points.push_back(Point(x1, y3));
    }
};