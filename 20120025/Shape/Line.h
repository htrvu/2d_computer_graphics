#pragma once
#include "./Shape.h"

class Line : public Shape {
private:
    bool isEdge;    // use in draw polygon edge

public:
    Line(Point start, Point end) : Shape(start, end) {
    }

    Line(Point start, Point end, RGBColor fillColor, int layer = -1) : Shape(start, end, fillColor, layer == -1) {
        if (layer == -1) {
            this->isEdge = false;
            name = "Line in layer " + to_string(layer);
        } else {
            this->isEdge = true;
            this->layer = layer;
        }
    }

public:
    // y = mx + b --> return {m, b}
    pair<float, float> getCoef() {
        int x1 = start.x();
        int y1 = start.y();
        int x2 = end.x();
        int y2 = end.y();

        float a = (x1 == x2) ? 0 : (float)(y2 - y1) / (x2 - x1);
        float b = y1 - a * x1;

        return make_pair(a, b);
    }

    static Point findIntersection(Line line1, Line line2) {
        pair<float, float> coef1 = line1.getCoef();
        pair<float, float> coef2 = line2.getCoef();

        float m1 = coef1.first, b1 = coef1.second;
        float m2 = coef2.first, b2 = coef2.second;

        if (m1 == m2) {
            return Point(-1, -1);
        }

        float x = (b2 - b1) / (m1 - m2);
        float y = m1 * x + b1;

        return Point(round(x), round(y));
    }

protected:
    void drawing(Canvas& canvas) {
        // Midpint
        // For line drawing, we does not draw it boundary like polygons
        int x1 = start.x();
        int y1 = start.y();
        int x2 = end.x();
        int y2 = end.y();

        if (abs(x2 - x1) > abs(y2 - y1)) {
            if (x1 > x2) {
                swap(x1, x2);
                swap(y1, y2);
            }

            int dx = x2 - x1;
            int dy = y2 - y1;

            int sign = (y2 - y1 > 0) ? 1 : -1;
            int p = 2 * dy - sign * dx;
            int x = x1, y = y1;
            while (x <= x2) {
                setPixel(x, y, layer, this->fillColor, canvas, isEdge);
                if (p >= 0) {
                    p = p + 2 * dy - (sign > 0) * sign * 2 * dx;
                    y = y + (sign > 0) * sign;
                } else {
                    p = p + 2 * dy - (sign < 0) * sign * 2 * dx;
                    y = y + (sign < 0) * sign;
                }
                x = x + 1;
            }
        } else {
            if (y1 > y2) {
                swap(x1, x2);
                swap(y1, y2);
            }

            int dx = x2 - x1;
            int dy = y2 - y1;

            int sign = (x2 - x1 > 0) ? 1 : -1;
            int p = - 2 * dx + sign * dy;
            int x = x1, y = y1;
            while (y <= y2) {
                setPixel(x, y, layer, this->fillColor, canvas, isEdge);
                if (p >= 0) {
                    p = p - 2 * dx + (sign < 0) * sign * 2 * dy;
                    x = x + (sign < 0) * sign;
                } else {
                    p = p - 2 * dx + (sign > 0) * sign * 2 * dy;;
                    x = x + (sign > 0) * sign;
                }
                y = y + 1;
            }
        }
    }

    void specifyInsidePixels(Canvas& canvas) {
        drawing(canvas);
    }

    // Boundary fill algorithm
    void filling(Canvas& canvas) {
        // We loop through each pixel and run boundary fill algorithm, this can deal with the case
        // when the line is not connected on the screen
        int x1 = start.x();
        int y1 = start.y();
        int x2 = end.x();
        int y2 = end.y();

        if (abs(x2 - x1) > abs(y2 - y1)) {
            if (x1 > x2) {
                swap(x1, x2);
                swap(y1, y2);
            }

            int dx = x2 - x1;
            int dy = y2 - y1;

            int sign = (y2 - y1 > 0) ? 1 : -1;
            int p = 2 * dy - sign * dx;
            int x = x1, y = y1;
            while (x <= x2) {
                Fill::boundaryFill(x, y, layer, this->fillColor, canvas, 8);
                if (p >= 0) {
                    p = p + 2 * dy - (sign > 0) * sign * 2 * dx;
                    y = y + (sign > 0) * sign;
                } else {
                    p = p + 2 * dy - (sign < 0) * sign * 2 * dx;
                    y = y + (sign < 0) * sign;
                }
                x = x + 1;
            }
        } else {
            if (y1 > y2) {
                swap(x1, x2);
                swap(y1, y2);
            }

            int dx = x2 - x1;
            int dy = y2 - y1;

            int sign = (x2 - x1 > 0) ? 1 : -1;
            int p = - 2 * dx + sign * dy;
            int x = x1, y = y1;
            while (y <= y2) {
                Fill::boundaryFill(x, y, layer, this->fillColor, canvas, 8);
                if (p >= 0) {
                    p = p - 2 * dx + (sign < 0) * sign * 2 * dy;
                    x = x + (sign < 0) * sign;
                } else {
                    p = p - 2 * dx + (sign > 0) * sign * 2 * dy;;
                    x = x + (sign > 0) * sign;
                }
                y = y + 1;
            }
        }
    }
};