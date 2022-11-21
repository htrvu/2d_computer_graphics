#pragma once
#include "./Shape.h"
#include <vector>

class Polygon: public Shape {
protected:
    vector<Point> points;       // in clockwise order

public:
    Polygon(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor) {
    }

protected:
    virtual void specifyVertices() {
        // Specifying points will be done in the derived classes
        // This function wil be called in the derived classes
        
        // Apply the transformation matrix to the vertices
        points = tMatrix.TransformPoints(points);
        
        // Re-specify the bounding box
        pair<Point, Point> newBB = findBoundingBox(points);
        topLeft = newBB.first;
        bottomRight = newBB.second;
    };

    virtual void specifyBoundingBox() {
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

        specifyVertices();
    }

protected:
    virtual void findFillPoint() {
        int x = 0, y = 0;
        if (points.size() > 0) {
            for (int i = 0; i < points.size(); i++) {
                x += points[i].x();
                y += points[i].y();
            }
            x /= points.size();
            y /= points.size();
        } else {
            int x1 = topLeft.x();
            int y1 = topLeft.y();
            int x2 = bottomRight.x();
            int y2 = bottomRight.y();
            x = (x1 + x2) / 2;
            y = (y1 + y2) / 2;
        }

        fillPoint = Point(clip(x, 0, WIN_WIDTH - 1), clip(y, 0, WIN_HEIGHT - 1));
    }


    void drawing(Canvas& canvas) {
        // draw boundary
        int n = points.size();
        for (int i = 0; i < n; i++) {
            Point p1 = points[i];
            Point p2 = points[(i + 1) % n];
            Line(p1, p2, Colors::BOUNDARY, layer).draw(canvas);
        }

        // fill
        filling(canvas);
    }

    void filling(Canvas& canvas) {
        if (points.size() == 0)
            return;
        Shape::filling(canvas);
    }
};