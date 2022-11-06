#include "./Colors.h"

RGBColor Colors::BLACK = RGBColor(0, 0, 0);
RGBColor Colors::WHITE = RGBColor(255, 255, 255);
RGBColor Colors::RED = RGBColor(255, 0, 0);
RGBColor Colors::GREEN = RGBColor(0, 255, 0);
RGBColor Colors::BLUE = RGBColor(0, 0, 255);
RGBColor Colors::YELLOW = RGBColor(255, 255, 0);
RGBColor Colors::MAGENTA = RGBColor(255, 0, 255);
RGBColor Colors::CYAN = RGBColor(0, 255, 255);
RGBColor Colors::ORANGE = RGBColor(255, 165, 0);

RGBColor Colors::NONE = RGBColor(-1, -1, -1);

RGBColor Colors::SELECTED = Colors::ORANGE;
RGBColor Colors::BOUNDARY = Colors::BLACK;

// Colors for filling
unordered_map<int, RGBColor> Colors::colorMap = {
    {C_RED, Colors::RED},
    {C_GREEN, Colors::GREEN},
    {C_BLUE, Colors::BLUE},
    {C_YELLOW, Colors::YELLOW}, 
    {C_MAGENTA, Colors::MAGENTA},
    {C_CYAN, Colors::CYAN}
};
