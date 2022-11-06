#pragma once
#include "./Shape.h"

class Ellipse: public Shape {
protected:
    Point topLeft, bottomRight; // boudary box
    Point center;
    int a, b;

public:
    Ellipse(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor) {
        topLeft = start;
        bottomRight = end;
        layer = Shape::layerCount;
        name = "Ellipse in layer " + to_string(layer);
        handlePoints();
    }

protected:
    void handlePoints() {
        center = start;
        a = abs(start.x() - end.x());
        b = abs(start.y() - end.y());

        int x1 = clip(start.x() - a, 0, WIN_WIDTH - 1);
        int y1 = clip(start.y() - b, 0, WIN_HEIGHT - 1);
        int x2 = clip(start.x() + a, 0, WIN_WIDTH - 1);
        int y2 = clip(start.y() + b, 0, WIN_HEIGHT - 1);

        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);

        topLeft = Point(x1, y1);
        bottomRight = Point(x2, y2);
    }

public:
    void setEnd(Point end) {
        Shape::setEnd(end);
        handlePoints();
    }

protected:
    // Set layer of cells insides this Ellipse to this->layer
    void specifyInsidePixels(Canvas& canvas) {
        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                if (pow(i - center.x(), 2) / pow(a, 2) + pow(j - center.y(), 2) / pow(b, 2) <= 1) {
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

    // MidPoint algorithm
    void drawing(Canvas& canvas) {
        if (a == 0 || b == 0) {
            return;
        }

        // draw boundary
        int xT = center.x(), yT = center.y();
        int x = 0, y = b;
        int p;
        int x0 = a * a * 1.0 / (sqrt(a * a + b * b));

        // First region
        p = a * a / 4 + b * b - a * a * b;
        while (x <= x0) {
            // Translate the points to its actual position then set pixels
            setPixel(x + xT, y + yT, layer, Colors::BOUNDARY, canvas, true);
            setPixel(-x + xT, y + yT, layer, Colors::BOUNDARY, canvas, true);
            setPixel(-x + xT, -y + yT, layer, Colors::BOUNDARY, canvas, true);
            setPixel(x + xT, -y + yT, layer, Colors::BOUNDARY, canvas, true);

            if (p < 0) {
                p += b * b * (2 * x + 3);
            } else {
                p += b * b * (2 * x + 3) - a * a * (2 * y - 2);
                y--;
            }
            x++;
        }

        // Second region
        p = b * b * (x + 1 / 2) * (x + 1 / 2) + a * a * (y - 1) * (y - 1) - a * a * b * b;
        while (y >= 0) {
            // Translate the points to its actual position then set pixels
            setPixel(x + xT, y + yT, layer, Colors::BOUNDARY, canvas, true);
            setPixel(-x + xT, y + yT, layer, Colors::BOUNDARY, canvas, true);
            setPixel(-x + xT, -y + yT, layer, Colors::BOUNDARY, canvas, true);
            setPixel(x + xT, -y + yT, layer, Colors::BOUNDARY, canvas, true);

            if (p < 0) {
                p += b * b * (2 * x + 2) - a * a * (2 * y - 3);
                x++;
            } else {
                p -= a * a * (2 * y - 3);
            }
            y--;
        }

        // inject layer and color value to pixels inside this Ellipse
        // (it likes to fill the rectangle in the first time. for later filling, we use boundary fill algorithm)
        specifyInsidePixels(canvas);
    }

    // Boundary fill algorithm
    void filling(Canvas& canvas) {
        int x1 = topLeft.x();
        int y1 = topLeft.y();
        int x2 = bottomRight.x();
        int y2 = bottomRight.y();

        // We loop through each pixel and run boundary fill algorithm, this can deal with the case
        // when the shape is not connected on the screen
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                Fill::boundaryFill(x, y, layer, this->fillColor, canvas);
            }
        }
    }

};