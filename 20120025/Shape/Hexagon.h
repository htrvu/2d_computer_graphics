#pragma once
#include "Polygon.h"

class Hexagon : public Polygon {
public:
    Hexagon(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Hexagon in layer " + to_string(layer);
    }

protected:
    virtual void specifyBoundingBox() {
        topLeft = start;
        bottomRight = end;
        squareAdjust(topLeft, bottomRight);
        specifyVertices();
    }

    void specifyVertices() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int side = min(abs(x1 - x2), abs(y1 - y2));
        x2 = x1 + side;
        y2 = y1 + side;

        Point p1(x1 + side / 2, y1);
        Point p2(x1, round(tan(30 * PI / 180) * side / 2 + y1));
        Point p3(x1, round(1.0 * y2 - tan(30 * PI / 180) * side / 2));
        Point p4(x1 + side / 2, y2);
        Point p5(x2, p3.y());
        Point p6(x2, p2.y());

        points = { p1, p2, p3, p4, p5, p6 };

        Polygon::specifyVertices();
    }
};