#pragma once
#include <vector>
#include "../Shape/Point.h"
using namespace std;

int random(int min, int max);
int clip(int value, int min, int max);

bool isDrawOption(int option);
bool isColorOption(int option);
bool isInScreen(int x, int y, int deltaX = 0, int deltaY = 0);
bool isAlign(Point start, Point end);

float sDistance(Point p1, Point p2);

// start will become topLeft, end will become bottomRight
void squareAdjust(Point& start, Point& end);

// Return the bounding box of a set of points (topLeft and bottomRight)
pair<Point, Point> findBoundingBox(vector<Point>& points);