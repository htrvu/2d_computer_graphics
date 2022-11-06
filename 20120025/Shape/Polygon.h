#pragma once
#include "./Shape.h"
#include <vector>

class Polygon: public Shape {
protected:
    vector<Point> points;       // clockwise
    Point topLeft, bottomRight; // boudary box

public:
    Polygon(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor) {
        topLeft = start;
        bottomRight = end;
        layer = Shape::layerCount;

        handlePoints();
    }

protected:
    virtual void specifyPoints() {};

    virtual void handlePoints() {
        int x1 = start.x();
        int y1 = start.y();
        int x2 = end.x();
        int y2 = end.y();

        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);

        topLeft = Point(x1, y1);
        bottomRight = Point(x2, y2);

        specifyPoints();
    }

public:
    void setEnd(Point end) {
        Shape::setEnd(end);
        handlePoints();
    }

protected:
    // Set layer of cells insides this polygon to this->layer
    void specifyInsidePixels(Canvas& canvas) {
        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                if (isInPolygon(points, Point(i, j))) {
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
    }

    void drawing(Canvas& canvas) {
        // draw boundary
        int n = points.size();
        for (int i = 0; i < n; i++) {
            Point p1 = points[i];
            Point p2 = points[(i + 1) % n];
            Line(p1, p2, Colors::BOUNDARY, layer).draw(canvas);
        }

        // specify layer and color value to pixels insided this polygon
        // (it likes to fill the polygon in the first time. for later filling, we use boundary fill algorithm)
        specifyInsidePixels(canvas);
    }

    // Boundary fill algorithm
    void filling(Canvas& canvas) {
        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        // We loop through each pixel and run boundary fill algorithm, this can deal with the case
        // when the polygon is not connected on the screen
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                Fill::boundaryFill(x, y, layer, this->fillColor, canvas);
            }
        }
    }

};