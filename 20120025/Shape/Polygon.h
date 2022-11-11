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
    virtual void specifyVertices() {};

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
    bool includes(Point p) {
        // From p, we draw a horizontal line to the right. If this line intersects an odd number 
        // of edge --> p is inside the polygon
        int n = points.size();
        vector<bool> skip(n, false);

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int p1_x = points[i].x();
            int p1_y = points[i].y();
            int p2_x = points[j].x();
            int p2_y = points[j].y();

            if (p.y() < min(p1_y, p2_y) || p.y() > max(p1_y, p2_y))
                continue;

            if (p.x() > max(p1_x, p2_x))
                continue;

            if (p1_y != p2_y) {
                float xIntersect = (float)(p.y() - p1_y) * (p2_x - p1_x) / (p2_y - p1_y) + p1_x;
                if (p1_x == p2_x)
                    xIntersect = p1_x;

                if (p.x() > xIntersect)
                    continue;

                if (p.x() == xIntersect)
                    return false;    // on the boundary

                // After checking boundary, we skip this edge if it is already counted before
                if (skip[i])
                    continue;

                // p.x() < xIntersect --> intersected
                // now we count the number of edges intersected
                if ((p1_x == p2_x && p.y() != p2_y && p.y() != p1_y) || (xIntersect != p1_x && xIntersect != p2_x)) {
                    cnt++;
                    continue;
                }

                Point mid, left, right;
                if (xIntersect == p1_x && p.y() == p1_y) {
                    if (skip[(i - 1 + n) % n]) {
                        cnt += 1;
                        continue;
                    }
                    left = points[(i - 1 + points.size()) % points.size()];
                    mid = points[i];
                    right = points[j];
                    skip[(i - 1 + n) % n] = true;   // skip the edge before this edge
                } else if (xIntersect == p2_x && p.y() == p2_y) {
                    if (skip[j]) {
                        cnt += 1;
                        continue;
                    }
                    left = points[i];
                    mid = points[j];
                    right = points[(j + 1) % n];    // next edge
                    skip[j] = true; // skip the next edge
                }

                if (left.y() == mid.y() || right.y() == mid.y() || (left.y() >= mid.y()) != (right.y() >= mid.y()))
                /* it looks like
                    \             \
                    --    or      ----
                    /
                */
                    cnt++;
                else
                /* it looks like
                    ____
                    /\
                    /  \
                */
                    cnt += 2;
            }
            else if (p.x() >= min(p1_x, p2_x) && p.y() == p1_y) {
                return false;    // on the boundary
            }
        }
        
        return cnt % 2 == 1;
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