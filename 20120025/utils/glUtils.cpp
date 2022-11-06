#include "./glUtils.h"
#include "../macros.h"

void init(int width, int height) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Top-left corner of window will be (0, 0)
    gluOrtho2D(0.0, width, height, 0.0);
}

void setPixel(int x, int y, int layer, RGBColor color, Canvas& canvas, bool boundary) {
    if (canvas.setCell(y, x, color, layer, boundary)) {
        glColor3ub(color.r(), color.g(), color.b());
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}

void changeMouseCursor(int cursorType) {
    switch (cursorType) {
        case IDLE:
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            break;
        case DRAWING:
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            break;
        case SELECTING:
            // glutSetCursor(GLUT_CURSOR_INFO);
            glutSetCursor(GLUT_CURSOR_TOP_SIDE);
            break;
        default:
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            break;
    }
}

void preventReshapeWindow(int w, int h) {
    glutReshapeWindow(WIN_WIDTH, WIN_HEIGHT);
}