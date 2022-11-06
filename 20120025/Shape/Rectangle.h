#pragma once
#include "./Polygon.h"
#include "./Line.h"

class Rectangle : public Polygon {
public:
    Rectangle(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Rectangle in layer " + to_string(layer);
    }

protected:
    virtual void handlePoints() {
        Polygon::handlePoints();
    }

    void specifyPoints() {
        points.clear();
        points.push_back(bottomRight);
        points.push_back(Point(bottomRight.x(), topLeft.y()));
        points.push_back(topLeft);
        points.push_back(Point(topLeft.x(), bottomRight.y()));
    }
};
