#pragma once
#include "../Canvas/RGBColor.h"
#include "../macros.h"
#include <unordered_map>
using namespace std;

class Colors {
public:
    static RGBColor BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, ORANGE;
    static RGBColor NONE;

    static RGBColor SELECTED;
    static RGBColor BOUNDARY;

public:
    static unordered_map<int, RGBColor> colorMap;
};