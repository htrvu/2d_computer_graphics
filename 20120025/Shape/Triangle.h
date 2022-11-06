#pragma once
#include "./Polygon.h"

class Triangle : public Polygon {
public:
    Triangle(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Triangle in layer " + to_string(layer);
    }

protected:
    virtual void handlePoints() {
        Polygon::handlePoints();
    }

    virtual void specifyPoints() {}
};
