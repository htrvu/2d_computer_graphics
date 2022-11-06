#pragma once

class RGBColor {
private:
    int mR, mG, mB;

public:
    RGBColor() {
        mR = mG = mB = 255;
    }

    RGBColor(int r, int g, int b) : mR(r), mG(g), mB(b) {}

public:
    void setColor(int r, int g, int b) {
        mR = r;
        mG = g;
        mB = b;
    }

    int r() {
        return mR;
    }

    int g() {
        return mG;
    }

    int b() {
        return mB;
    }

public:
    RGBColor darker() {
        return RGBColor(mR * 0.75, mG * 0.75, mB * 0.75);
    }

public:
    bool operator==(RGBColor other) {
        return mR == other.mR && mG == other.mG && mB == other.mB;
    }

    bool operator!=(RGBColor other) {
        return !(*this == other);
    }
};