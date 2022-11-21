#pragma once

class RGBColor {
private:
    int mR, mG, mB;
    int mOriginalR, mOriginalG, mOriginalB;

public:
    RGBColor() {
        mR = mG = mB = 255;
        mOriginalR = mOriginalG = mOriginalB = 255;
    }

    RGBColor(int r, int g, int b) {
        mR = mOriginalR = r;
        mG = mOriginalG = g;
        mB = mOriginalB = b;
    }

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
    void darken() {
        if (mR == mOriginalR && mG == mOriginalG && mB == mOriginalB) {
            mR *= 0.75;
            mG *= 0.75;
            mB *= 0.75;
        }
    }

    void reset() {
        mR = mOriginalR;
        mG = mOriginalG;
        mB = mOriginalB;
    }



public:
    bool operator==(RGBColor other) {
        return mR == other.mR && mG == other.mG && mB == other.mB;
    }

    bool operator!=(RGBColor other) {
        return !(*this == other);
    }
};