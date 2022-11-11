#pragma once
#include "Triangle.h"

class IsosRightTriangle : public Triangle {
public:
    IsosRightTriangle(Point start, Point end, RGBColor fillColor) : Triangle(start, end, fillColor) {
        name = "Isosceles Right Triangle in layer " + to_string(layer);
    }

protected:
    void specifyBoundingBox() {
        topLeft = start;
        bottomRight = end;
        squareAdjust(topLeft, bottomRight);
        specifyVertices();
    }

    virtual void specifyVertices() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int side = min(abs(x1 - x2), abs(y1 - y2));
        x2 = x1 + side;
        y2 = y1 + side;

        points.push_back(Point(x2, y2));
        points.push_back(Point(x1, y1));
        points.push_back(Point(x1, y2));
    }
};