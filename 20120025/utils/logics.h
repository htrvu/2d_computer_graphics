#pragma once
#include <vector>
#include "../Shape/Point.h"
using namespace std;

int random(int min, int max);
int clip(int value, int min, int max);

bool isDrawOption(int option);
bool isColorOption(int option);
bool isInScreen(int x, int y);

bool isInPolygon(vector<Point>& points, Point p);

float sDistance(Point p1, Point p2);