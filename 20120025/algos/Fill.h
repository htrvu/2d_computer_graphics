#pragma once
#include "../Canvas/Canvas.h"
#include "../utils/glUtils.h"
#include "../utils/logics.h"
#include <iostream>
#include <stack>
using namespace std;

class Fill {
public:
    static void boundaryFill(int x, int y, int layer, RGBColor fillColor, Canvas& canvas, int nDirect = 4) {
        // Non-recursive implementation
        stack<pair<int, int>> s;
        s.push(make_pair(x, y));
        while (!s.empty()) {
            pair<int, int> p = s.top();
            s.pop();

            int x = p.first, y = p.second;
            Cell cell = canvas.getCell(y, x);
            if (cell.getLayer() != layer || cell.getColor() == fillColor || cell.isBoundary()) {
                continue;
            }

            setPixel(x, y, layer, fillColor, canvas, false);

            if (isInScreen(x + 1, y))
                s.push(make_pair(x + 1, y));
            if (isInScreen(x - 1, y))
                s.push(make_pair(x - 1, y));
            if (isInScreen(x, y + 1))
                s.push(make_pair(x, y + 1));
            if (isInScreen(x, y - 1))
                s.push(make_pair(x, y - 1));

            if (nDirect == 8) {
                if (isInScreen(x + 1, y + 1))
                    s.push(make_pair(x + 1, y + 1));
                if (isInScreen(x - 1, y - 1))
                    s.push(make_pair(x - 1, y - 1));
                if (isInScreen(x + 1, y - 1))
                    s.push(make_pair(x + 1, y - 1));
                if (isInScreen(x - 1, y + 1))
                    s.push(make_pair(x - 1, y + 1));
            }
        }
    }
};