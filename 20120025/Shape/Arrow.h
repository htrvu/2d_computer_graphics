#pragma once
#include "Polygon.h"

class Arrow : public Polygon {
public:
    Arrow(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Arrow in layer " + to_string(layer);
    }

protected:
    virtual void specifyBoundingBox() {
        Polygon::specifyBoundingBox();
    }

    void specifyVertices() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);

        Point p1(x2, y1 + height / 2);
        Point p2(x1 + 2 * width / 3, y1);
        Point p3(p2.x(), y1 + height / 4);
        Point p4(x1, p3.y());
        Point p5(x1, y1 + 3 * height / 4);
        Point p6(p2.x(), p5.y());
        Point p7(p2.x(), y2);

        points = { p1, p2, p3, p4, p5, p6, p7 };
    }
};