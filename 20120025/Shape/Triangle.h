#pragma once
#include "./Polygon.h"

class Triangle : public Polygon {
public:
    Triangle(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        name = "Triangle in layer " + to_string(layer);
    }

protected:
    virtual void specifyBoundingBox() {
        Polygon::specifyBoundingBox();
    }

    virtual void specifyVertices() {}
};
