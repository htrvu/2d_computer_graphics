#pragma once
#include "./Shape.h"
#include "./Line.h"

class Ellipse: public Shape {
protected:
    Point center;
    int a, b;
    bool scaled = false;

public:
    Ellipse(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor) {
        name = "Ellipse in layer " + to_string(layer);
        specifyBoundingBox();
    }

protected:
    void specifyBoundingBox() {
        center = start;

        if (!scaled) {
            // a and b from draw event
            a = abs(start.x() - end.x());
            if (a > center.x())
                a = center.x();
            b = abs(start.y() - end.y());
            if (b > center.y())
                b = center.y();
        }

        int x1 = clip(center.x() - a, 0, WIN_WIDTH - 1);
        int y1 = clip(center.y() - b, 0, WIN_HEIGHT - 1);
        int x2 = clip(center.x() + a, 0, WIN_WIDTH - 1);
        int y2 = clip(center.y() + b, 0, WIN_HEIGHT - 1);

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
        if (a <= 0 || b <= 0) {
            return;
        }

        // Draw boundary
        int xT = center.x(), yT = center.y();
        int x = 0, y = b;
        int p;
        int x0 = round(a * a * 1.0 / (sqrt(a * a + b * b)));

        Point startPoint = tMatrix.TransformPoint(Point(x + xT, y + yT));
        int minX = startPoint.x(), maxX = startPoint.x();
        int minY = startPoint.y(), maxY = startPoint.y();

        vector<Point> prevPoints;
        // First region
        p = round(a * a / 4 + b * b - a * a * b);
        while (x <= x0) {
            // Translate the points to its actual position then set pixels
            vector<Point> points = {
                Point(x + xT, y + yT),
                Point(-x + xT, y + yT),
                Point(x + xT, -y + yT),
                Point(-x + xT, -y + yT)
            };
            vector<Point> tmp;
            for (int i = 0; i < 4; i++) {
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
                p += b * b * (2 * x + 3);
            } else {
                p += b * b * (2 * x + 3) - a * a * (2 * y - 2);
                y--;
            }
            x++;
        }

        // Second region
        p = round(b * b * (x + 1 / 2) * (x + 1 / 2) + a * a * (y - 1) * (y - 1) - a * a * b * b);
        while (y >= 0) {
            vector<Point> points = {
                Point(x + xT, y + yT),
                Point(-x + xT, y + yT),
                Point(x + xT, -y + yT),
                Point(-x + xT, -y + yT)
            };
            vector<Point> tmp;
            for (int i = 0; i < 4; i++) {
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
                p += b * b * (2 * x + 2) - a * a * (2 * y - 3);
                x++;
            } else {
                p -= a * a * (2 * y - 3);
            }
            y--;
        }

        // specify the actual bounding box
        topLeft = Point(minX, minY);
        bottomRight = Point(maxX, maxY);

        fill(canvas);
    }
};