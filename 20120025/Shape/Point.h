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

    void setX(int x) {
        mX = x;
    }

    void setY(int y) {
        mY = y;
    }

public:
    Point operator+(const Point& p) {
        return Point(mX + p.mX, mY + p.mY);
    }

    Point operator/(const int& n) {
        return Point(mX / n, mY / n);
    }

    bool operator==(const Point& p) {
        return mX == p.mX && mY == p.mY;
    }
};