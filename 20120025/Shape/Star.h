#pragma once
#include "Polygon.h"

class Star : public Polygon {
public:
    Star(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Star in layer " + to_string(layer);
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

        // Otherwise, we could find the m_i points based on a pentagon (but width and height must be equal)
        Point m1(x1 + width / 2, y1);
        Point m2(x1, y1 + height * 3 / 10);
        Point m3(x1 + width * 1 / 5, y2);
        Point m4(x1 + width * 4 / 5, y2);
        Point m5(x2, y1 + height * 3 / 10);

        Point i12 = Line::findIntersection(Line(m1, m3), Line(m2, m5));
        Point i23 = Line::findIntersection(Line(m2, m4), Line(m1, m3));
        Point i34 = Line::findIntersection(Line(m3, m5), Line(m2, m4));
        Point i45 = Line::findIntersection(Line(m4, m1), Line(m3, m5));
        Point i51 = Line::findIntersection(Line(m5, m2), Line(m4, m1));

        if (i12.x() == -1 || i12.y() == -1) {
            points = { m1 };
            return;
        }

        points = { m1, i12, m2, i23, m3, i34, m4, i45, m5, i51 };
    }
};