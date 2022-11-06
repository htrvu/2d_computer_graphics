#pragma once
#include <GL/glut.h>
#include "../Canvas/Canvas.h"

void init(int width, int height);
void setPixel(int x, int y, int layer, RGBColor color, Canvas& canvas, bool boundary);

void changeMouseCursor(int cursorType);
void preventReshapeWindow(int w, int h);