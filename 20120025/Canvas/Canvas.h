#pragma once
#include "./Cell.h"
#include "../Constants/Colors.h"
// #include "../utils/logics.h"
// #include "../utils/glUtils.h"
#include <vector>
#include <iostream>
using namespace std;

class Canvas {
private:
    int width;
    int height;
    vector<vector<Cell>> cells;

public:
    Canvas() {
        width = 0;
        height = 0;
    }

    Canvas(int width, int height) : width(width), height(height) {
        for (int i = 0; i < height; i++) {
            cells.push_back(vector<Cell>(width, Cell()));
        }
    }

public:
    // NOTICE: x and y are n_row and n_column of the array, not the actual coordinate

    Cell getCell(int x, int y) {
        return cells[x][y];
    }

    bool setCell(int x, int y, RGBColor color, int layer, bool boundary) {
        if (x < 0 || x >= height || y < 0 || y >= width) {
            return false;
        }
        
        if (layer >= cells[x][y].getLayer()) {
            cells[x][y].setCell(color, layer, boundary);
            return true;
        }
        return false;
    }

    void setCellLayer(int x, int y, int layer) {
        cells[x][y].setLayer(layer);
    }

    void clear() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cells[i][j].clear();
            }
        }
    }
};