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

bool isInScreen(int x, int y, int deltaX, int deltaY) {
    return (x >= deltaX && x < WIN_WIDTH - deltaX && y >= deltaY && y < WIN_HEIGHT - deltaY);
}

bool isAlign(Point start, Point end) {
    return (start.x() == end.x() || start.y() == end.y());
}

// Square of Euclid distance
float sDistance(Point p1, Point p2) {
    return pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2);
}

void squareAdjust(Point& start, Point& end) {
    int x1 = start.x();
    int y1 = start.y();
    int x2 = end.x();
    int y2 = end.y();

    int width = abs(x1 - x2);
    int height = abs(y1 - y2);
    int side = min(width, height);

    if (y1 < y2) {
        if (x1 < x2)
            start = Point(x1, y1);
        else
            start = Point(x1 - side, y1);
    } else {
        if (x1 < x2)
            start = Point(x1, y1 - side);
        else
            start = Point(x1 - side, y1 - side);
    }

    end = Point(start.x() + side, start.y() + side);
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