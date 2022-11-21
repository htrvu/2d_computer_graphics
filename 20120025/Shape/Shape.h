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
#include "../Matrix/Matrix.h"
using namespace std;

class Shape {
protected:
    int layer;
    string name;
    RGBColor fillColor;
    bool isSelecting = false;
    Point fillPoint;    // starting point for filling
    Point start, end;   // start and end point in mouse events
    Point topLeft, bottomRight; // boundary box
    Matrix tMatrix;  // transformation matrix

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

public:
    void setFillColor(RGBColor fillColor) {
        this->fillColor = fillColor;
    }

protected:
    // specify the bounding box of shape (topLeft and bottomRight) from start and end
    virtual void specifyBoundingBox() {
        topLeft = start;
        bottomRight = end;
    }

    virtual void findFillPoint() {}

    virtual void drawing(Canvas& canvas) {}

    virtual void filling(Canvas& canvas) {
        if (isAlign(start, end) || isAlign(topLeft, bottomRight))
            return;
        findFillPoint();
        if (canvas.getCell(fillPoint.x(), fillPoint.y()).isBoundary())
            return;
        Fill::boundaryFill(fillPoint.x(), fillPoint.y(), layer, fillColor, canvas);
    }

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

public:
    void draw(Canvas& canvas, RGBColor fillColor = Colors::NONE) {
        if (fillColor != Colors::NONE) {
            this->fillColor = fillColor;
        }

        if (isSelecting)
            this->fillColor.darken();
        else
            this->fillColor.reset();

        drawing(canvas);
    }

    void setSelecting(bool isSelecting) {
        this->isSelecting = isSelecting;
    }

    void fill(Canvas& canvas, RGBColor fillColor = Colors::NONE) {
        if (fillColor != Colors::NONE) {
            this->fillColor = fillColor;
        }

        if (isSelecting)
            this->fillColor.darken();
        else
            this->fillColor.reset();

        filling(canvas);
    }

public:
    // Transformations

    virtual void translate(double dx, double dy) {
        // Do not allow to translate fillPoint outside the window
        if (!isInScreen(fillPoint.x() + dx, fillPoint.y() + dy, 10, 10))
            return;

        tMatrix.Translate(dx, dy);
        specifyBoundingBox();
    }

    virtual void rotate(double angle) {
        // Rotate around center of shape
        int xC = (topLeft.x() + bottomRight.x()) / 2;
        int yC = (topLeft.y() + bottomRight.y()) / 2;
        tMatrix.Translate(-xC, -yC);
        tMatrix.Rotate(angle);
        tMatrix.Translate(xC, yC);
        specifyBoundingBox();
    }

    virtual void scale(double sx, double sy) {
        // Keep the center of shape unchanged after scaling
        int xC = (topLeft.x() + bottomRight.x()) / 2;
        int yC = (topLeft.y() + bottomRight.y()) / 2;
        int newXC = sx * xC;
        int newYC = sy * yC;

        tMatrix.Scale(sx, sy);
        tMatrix.Translate(xC - newXC, yC - newYC);
        specifyBoundingBox();
    }
};