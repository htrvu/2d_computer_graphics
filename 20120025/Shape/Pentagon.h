#pragma once
#include "Polygon.h"

class Pentagon : public Polygon {
public:
    Pentagon(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Pentagon in layer " + to_string(layer);
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
        Point p2(x1, round(tan(36 * PI / 180) * side / 2 + y1));
        Point p3(round(tan(18.0 * PI / 180) * (y2 - p2.y()) + x1), y2);
        Point p4(round(1.0 * x2 - tan(18.0 * PI / 180) * (y2 - p2.y())), y2);
        Point p5(x2, p2.y());

        points = { p1, p2, p3, p4, p5 };
    }
};