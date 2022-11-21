#pragma once
#include "Polygon.h"
#include "Line.h"

class Add : public Polygon {
public:
    Add(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Add Operator in layer " + to_string(layer);
    }

protected:
    void specifyVertices() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);

        Point p1(x1 + width / 3, y1);
        Point p2(x1 + width / 3, y1 + height / 3);
        Point p3(x1, y1 + height / 3);
        Point p4(x1, y1 + 2 * height / 3);
        Point p5(x1 + width / 3, y1 + 2 * height / 3);
        Point p6(x1 + width / 3, y2);
        Point p7(x1 + 2 * width / 3, y2);
        Point p8(x1 + 2 * width / 3, y1 + 2 * height / 3);
        Point p9(x2, y1 + 2 * height / 3);
        Point p10(x2, y1 + height / 3);
        Point p11(x1 + 2 * width / 3, y1 + height / 3);
        Point p12(x1 + 2 * width / 3, y1);

        points = { p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 };

        Polygon::specifyVertices();
    }
};


class Minus : public Polygon {
public:
    Minus(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Minus Operator in layer " + to_string(layer);
    }

protected:
    void specifyVertices() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);

        Point p1(x1, y1 + height / 3);
        Point p2(x1, y1 + 2 * height / 3);
        Point p3(x2, y1 + 2 * height / 3);
        Point p4(x2, y1 + height / 3);

        points = { p1, p2, p3, p4 };

        Polygon::specifyVertices();
    }
};


class Times : public Polygon {
public:
    Times(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Times Operator in layer " + to_string(layer);
    }

protected:
    void specifyVertices() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);

        Point m1(x1 + width / 5, y1);
        Point m2(x1, y1 + height / 5);
        Point m3(x1, y1 + 4 * height / 5);
        Point m4(x1 + width / 5, y2);
        Point m5(x1 + 4 * width / 5, y2);
        Point m6(x2, y1 + 4 * height / 5);
        Point m7(x2, y1 + height / 5);
        Point m8(x1 + 4 * width / 5, y1);

        Point i23 = Line::findIntersection(Line(m2, m5), Line(m3, m8));
        Point i45 = Line::findIntersection(Line(m4, m7), Line(m5, m2));
        Point i67 = Line::findIntersection(Line(m6, m1), Line(m7, m4));
        Point i81 = Line::findIntersection(Line(m8, m3), Line(m1, m6));

        points = { m1, m2, i23, m3, m4, i45, m5, m6, i67, m7, m8, i81 };

        Polygon::specifyVertices();
    }
};


class Divide : public Polygon {
public:
    Divide(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Divide Operator in layer " + to_string(layer);
    }

protected:
    void specifyVertices() {
        points.clear();

        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);

        Point p1(x1 + 4 * width / 5, y1);
        Point p2(x1, y2);
        Point p3(x1 + width / 5, y2);
        Point p4(x2, y1);
        
        points = { p1, p2, p3, p4 };

        Polygon::specifyVertices();
    }
};