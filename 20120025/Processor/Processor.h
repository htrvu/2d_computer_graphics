#pragma once
#include "../utils/logics.h"
#include "../utils/glUtils.h"
#include "../Canvas/Canvas.h"
#include "../Storage/Storage.h"
#include <iostream>
using namespace std;

class Processor {
public:
    static int option;

    static int window;
    static Canvas canvas;
    static Storage storage;
    
    static bool isDrawing;
    static int currentDrawOption;
    static Shape* newShape;

    static RGBColor pickingColor;

    static bool isSelecting;
    static Shape* selectingShape;

private:
    static void reset();

public:
    static void menuEvents(int value);
    static void createMenu();

public:
    static void mousePressed(int button, int state, int x, int y);
    static void mouseMove(int x, int y);

public:
    static void normalKeyPressed(unsigned char key, int x, int y);
    static void specialKeyPressed(int key, int x, int y);

public:
    static void display();
};
