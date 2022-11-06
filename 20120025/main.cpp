#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "./macros.h"
#include "Canvas/Canvas.h"
#include "utils/glUtils.h"
#include "Processor/Processor.h"

using namespace std;


int main(int argc, char** argv) {
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    cout << "Hoang Trong Vu - 20120025 - CNTN20" << endl;
    cout << "Computer graphics - Lab 2: Draw and fill 2d objects" << endl;
    cout << "-----------------------------------------------------------------" << endl << endl;
     
    srand(time(NULL));

    // Init window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    Processor::window = glutCreateWindow("Hoang Trong Vu - 20120025 - CNTN20");

    init(WIN_WIDTH, WIN_HEIGHT);
    
    // Create canvas object
    Processor::canvas = Canvas(WIN_WIDTH, WIN_HEIGHT);

    // Create menu
    Processor::createMenu();

    // Mouse events
    glutMouseFunc(Processor::mousePressed);
    glutMotionFunc(Processor::mouseMove);

    changeMouseCursor(IDLE);

    // Window events
    glutReshapeFunc(preventReshapeWindow);

    // Run
    glutDisplayFunc(Processor::display);
    glutMainLoop();

    return EXIT_SUCCESS;
}