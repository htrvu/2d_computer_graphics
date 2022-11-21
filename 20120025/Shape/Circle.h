#pragma once
#include "./Shape.h"

class Circle: public Shape {
protected:
    Point center;
    int radius;
    bool scaled = false;

public:
    Circle(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor) {
        name = "Circle in layer " + to_string(layer);
        specifyBoundingBox();
    }

protected:
    void specifyBoundingBox() {
        center = start;

        if (!scaled) {
            // radius from draw event
            radius = sqrt(sDistance(start, end));
            int maxRadius = min(center.x(), center.y());
            if (radius > maxRadius)
                radius = maxRadius;
        }
        
        int x1 = clip(center.x() - radius, 0, WIN_WIDTH - 1);
        int y1 = clip(center.y() - radius, 0, WIN_HEIGHT - 1);
        int x2 = clip(center.x() + radius, 0, WIN_WIDTH - 1);
        int y2 = clip(center.y() + radius, 0, WIN_HEIGHT - 1);

        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);

        topLeft = Point(x1, y1);
        bottomRight = Point(x2, y2);
    }

    void findFillPoint() {
        fillPoint = tMatrix.TransformPoint(center);
    }

protected:
    // MidPoint algorithm
    void drawing(Canvas& canvas) {
        // Draw boundary
        int x = 0, y = radius;
        int xT = center.x(), yT = center.y();
        int p = 1 - radius;

        Point startPoint = tMatrix.TransformPoint(Point(x + xT, y + yT));
        int minX = startPoint.x(), maxX = startPoint.x();
        int minY = startPoint.y(), maxY = startPoint.y();

        vector<Point> prevPoints;
        while (x <= y) {
            vector<Point> points = {
                Point(x + xT, y + yT),
                Point(y + xT, x + yT),
                Point(-x + xT, y + yT),
                Point(-y + xT, x + yT),
                Point(-x + xT, -y + yT),
                Point(-y + xT, -x + yT),
                Point(x + xT, -y + yT),
                Point(y + xT, -x + yT)
            };
            vector<Point> tmp;
            for (int i = 0; i < 8; i++) {
                Point newP = tMatrix.TransformPoint(points[i]);
                if (prevPoints.size() > 0) {
                    Point prevP = prevPoints[i];
                    Line(prevP, newP, Colors::BOUNDARY, layer).draw(canvas);
                }
                tmp.push_back(newP);
                setPixel(newP.x(), newP.y(), layer, Colors::BOUNDARY, canvas, true);
                minX = min(minX, newP.x());
                maxX = max(maxX, newP.x());
                minY = min(minY, newP.y());
                maxY = max(maxY, newP.y());
            }
            prevPoints = tmp;

            if (p < 0) {
                p += 2 * x + 3;
            } else {
                p += 2 * (x - y) + 3;
                y--;
            }
            x++;
        }

        // specify the actual bounding box
        topLeft = Point(minX, minY);
        bottomRight = Point(maxX, maxY);

        // fill
        filling(canvas);
    }
};