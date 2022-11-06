#pragma once
#include "./RGBColor.h"
#include "../Constants/Colors.h"

class Cell {
private:
    RGBColor color;
    int layer;
    bool boundary;

public:
    Cell(RGBColor color = Colors::WHITE) {
        this->color = color;
        layer = 0;
        boundary = false;
    }

public:
    void setCell(RGBColor color, int layer = 0, bool boundary = false) {
        this->color.setColor(color.r(), color.g(), color.b());
        this->layer = layer;
        this->boundary = boundary;
    }

    void setColor(RGBColor color) {
        this->color = color;
    }

    void setLayer(int layer) {
        this->layer = layer;
    }

    RGBColor getColor() {
        return color;
    }

    int getLayer() {
        return layer;
    }

    bool isBoundary() {
        return boundary;
    }

    void clear() {
        color = Colors::WHITE;
        layer = 0;
        boundary = false;
    }
};