#pragma once
#include <iostream>
#include <string>
#include "./Point.h"
#include "../Clock/Clock.h"
#include "../macros.h"
#include "../utils/logics.h"
#include "../utils/glUtils.h"
#include "../Canvas/Canvas.h"
#include "../Constants/Colors.h"
#include "../algos/Fill.h"
using namespace std;

class Shape {
protected:
    int layer;
    string name;
    RGBColor fillColor;
    bool shouldFill = false;
    Point start, end;   // start and end point in mouse events

public:
    static int layerCount;

public:
    Shape(Point start, Point end) {
        this->start = start;
        this->end = end;
    }

    Shape(Point start, Point end, RGBColor fillColor) : start(start), end(end), fillColor(fillColor) {
        layerCount++;
    }

    virtual ~Shape() {}

protected:
    virtual void drawing(Canvas& canvas) {};
    virtual void filling(Canvas& canvas) {};
    virtual void specifyInsidePixels(Canvas& canvas) {};

public:
    virtual void setEnd(Point end) {
        int x = end.x();
        int y = end.y();

        x = clip(x, 0, WIN_WIDTH - 1);
        y = clip(y, 0, WIN_HEIGHT - 1);

        this->end = Point(x, y);
    }

public:
    string getName() {
        return name;
    }

    int getShapeLayer() {
        return layer;
    }

    void setFillColor(RGBColor color) {
        fillColor = color;
    }

    void setShouldFill(bool shouldFill) {
        this->shouldFill = shouldFill;
    }

public:
    void draw(Canvas& canvas, RGBColor fillColor = Colors::NONE) {
        if (fillColor != Colors::NONE) {
            this->fillColor = fillColor;
        }

        drawing(canvas);
    }

    void select(Canvas& canvas) {
        RGBColor tmp = fillColor;
        fillColor = fillColor.darker();
        specifyInsidePixels(canvas);
        fillColor = tmp;
    }

    void deselect(Canvas& canvas) {
        specifyInsidePixels(canvas);
    }

    void fill(Canvas& canvas, RGBColor fillColor = Colors::NONE) {
        if (fillColor != Colors::NONE) {
            this->fillColor = fillColor;
        }

        // layer == -1 means this shape is a part of other shape (ex. Line and Rectangle)
        if (layer != -1)
            cout << "Filling " << name << " with Boundary Fill algorithm" << endl;
        
        Clock clock;

        clock.start();
        filling(canvas);
        clock.stop();

        if (layer != -1) {
            cout << "Time: " << clock.getTime() << " ms" << endl;
            cout << "----------------------------------------------" << endl;
        }
    }
};