#pragma once

class Point {
private:
    int mX, mY;

public:
    Point(int x = 0, int y = 0) : mX(x), mY(y) {}

public:
    int x() {
        return mX;
    }

    int y() {
        return mY;
    }
};