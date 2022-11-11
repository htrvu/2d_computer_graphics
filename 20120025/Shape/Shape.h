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
    Point topLeft, bottomRight; // boudary box

public:
    static int layerCount;

public:
    Shape(Point start, Point end) {
        this->start = start;
        this->end = end;
    }

    Shape(Point start, Point end, RGBColor fillColor, bool autoSetLayer = true) : start(start), end(end), fillColor(fillColor) {
        if (autoSetLayer) {
            layerCount++;
            layer = layerCount;
        }

        specifyBoundingBox();
    }

    virtual ~Shape() {}

protected:
    // specify the bounding box of shape (topLeft and bottomRight) from start and end
    virtual void specifyBoundingBox() {
        topLeft = start;
        bottomRight = end;
    }

    virtual bool includes(Point p) {
        return false;
    }

    virtual void drawing(Canvas& canvas) {};
    virtual void filling(Canvas& canvas) {};

    virtual void specifyInsidePixels(Canvas& canvas) {
        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                if (includes(Point(i, j))) {
                    int k = j;
                    Cell cell = canvas.getCell(k, i);
                    while (k <= y2 && (cell.getLayer() < layer || (cell.getLayer() == layer && !cell.isBoundary()))) {
                        setPixel(i, k, layer, fillColor, canvas, false);
                        k++;
                        if (k <= y2)
                            cell = canvas.getCell(k, i);
                    }
                    if (k > j)
                        j = k - 1;
                }
            }
        }
    };

public:
    virtual void setEnd(Point end) {
        int x = end.x();
        int y = end.y();

        x = clip(x, 0, WIN_WIDTH - 1);
        y = clip(y, 0, WIN_HEIGHT - 1);

        this->end = Point(x, y);

        specifyBoundingBox();
    }

public:
    string getName() {
        return name;
    }

    int getShapeLayer() {
        return layer;
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