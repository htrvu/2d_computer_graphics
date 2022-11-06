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

// Check if a point is inside a polygon (on the boundary is considered inside)
bool isInPolygon(vector<Point>& points, Point p) {
    // points is in clockwise order

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

            // if ((left.y() >= mid.y()) != (right.y() >= mid.y()))
            // if ((left.y() > mid.y()) != (right.y() > mid.y()))
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

// Square of Euclid distance
float sDistance(Point p1, Point p2) {
    return pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2);
}