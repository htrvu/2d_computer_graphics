#include <cstdlib>
#include <cmath>
#include "./logics.h"
#include "../macros.h"

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

int clip(int value, int min, int max) {
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

bool isDrawOption(int option) {
    return (option >= LINE && option <= DIVIDE);
}

bool isColorOption(int option) {
    return (option >= C_BLACK && option <= C_CYAN);
}

bool isInScreen(int x, int y) {
    return (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT);
}

// Square of Euclid distance
float sDistance(Point p1, Point p2) {
    return pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2);
}

void squareAdjust(Point& topLeft, Point& bottomRight) {
    int x1 = topLeft.x();
    int y1 = topLeft.y();
    int x2 = bottomRight.x();
    int y2 = bottomRight.y();

    int width = abs(x1 - x2);
    int height = abs(y1 - y2);
    int side = min(width, height);

    if (y1 < y2) {
        if (x1 < x2)
            topLeft = Point(x1, y1);
        else
            topLeft = Point(x1 - side, y1);
    } else {
        if (x1 < x2)
            topLeft = Point(x1, y1 - side);
        else
            topLeft = Point(x1 - side, y1 - side);
    }

    bottomRight = Point(topLeft.x() + side, topLeft.y() + side);
}

pair<Point, Point> findBoundingBox(vector<Point>& points) {
    int minX = points[0].x();
    int maxX = minX;
    int minY = points[0].y();
    int maxY = minY;

    for (int i = 1; i < points.size(); i++) {
        int x = points[i].x();
        int y = points[i].y();

        if (x < minX)
            minX = x;
        if (x > maxX)
            maxX = x;
        if (y < minY)
            minY = y;
        if (y > maxY)
            maxY = y;
    }

    return make_pair(Point(minX, minY), Point(maxX, maxY));
}