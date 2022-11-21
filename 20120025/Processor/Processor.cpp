#include <GL/glut.h>
#include "Processor.h"
#include "../Shape/index.h"

// Static attributes

int Shape::layerCount = 0;

int Processor::window = 0;
int Processor::option = -1;
Canvas Processor::canvas = Canvas();
Storage Processor::storage = Storage();

int Processor::currentDrawOption = -1;
bool Processor::isDrawing = false;
Shape* Processor::newShape = nullptr;

RGBColor Processor::pickingColor = Colors::GREEN;

bool Processor::isSelecting = false;
Shape* Processor::selectingShape = nullptr;

////////////////////////////////////////////////////////////////

// Functions

void Processor::reset() {
    isDrawing = false;
    newShape = nullptr;
    selectingShape = nullptr;
    // shouldFillSelectingShape = false;
    currentDrawOption = -1;
    isSelecting = false;
    canvas.clear();
    storage.clear();
}

void Processor::menuEvents(int value) {
    if (value == 0) {
        glutDestroyWindow(window);
        storage.clear();
        exit(0);
    } else {
        option = value;
    }

    if (option == CLEAR) {
        changeMouseCursor(IDLE);
        Processor::reset();
        Shape::layerCount = 0;
        glutPostRedisplay();
    }
    else if (isColorOption(option)) {
        pickingColor = Colors::colorMap[option];
        if (selectingShape) {
            selectingShape->setFillColor(pickingColor);
            // shouldFillSelectingShape = true;
            // shouldRedraw = false;
            glutPostRedisplay();
        } else {
            // shouldFillSelectingShape = false;
        }
    }
    else if (isDrawOption(option)) {
        changeMouseCursor(DRAWING);

        currentDrawOption = option;
        isSelecting = false;

        if (selectingShape) {
            // selectingShape->deselect(canvas);
            selectingShape->setSelecting(false);
            selectingShape = nullptr;
            // shouldRedraw = false;
            glutPostRedisplay();
        }
    }
    else if (option == PICK_SHAPE) {
        changeMouseCursor(SELECTING);
        currentDrawOption = -1;
        isSelecting = true;
    }
    else if (option == DELETE_SHAPE) {
        if (selectingShape) {
            storage.removeShape(selectingShape->getShapeLayer());
            selectingShape = nullptr;
            // shouldFillSelectingShape = false;
            // shouldRedraw = true;
            glutPostRedisplay();
        }
    }
}

void Processor::createMenu(void) {
    int triangle_menu = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Equilateral Triangle", EQ_TRIANGLE);
    glutAddMenuEntry("Isosceles Right Triangle", ISOR_TRIANGLE);

    int quad_menu = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Rectangle", RECTANGLE);
    glutAddMenuEntry("Square", SQUARE);

    int oval_menu = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Circle", CIRCLE);
    glutAddMenuEntry("Ellipse", ELLIPSE);

    int re_poly_menu = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Pentagon", PENTAGON);
    glutAddMenuEntry("Hexagon", HEXAGON);

    int other_menu = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Arrow", ARROW);
    glutAddMenuEntry("Star", STAR);

    int ope_menu = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Add", ADD);
    glutAddMenuEntry("Minus", MINUS);
    glutAddMenuEntry("Times", TIMES);
    glutAddMenuEntry("Divides", DIVIDE);

    int color_menu = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Red", C_RED);
    glutAddMenuEntry("Green", C_GREEN);
    glutAddMenuEntry("Blue", C_BLUE);
    glutAddMenuEntry("Yellow", C_YELLOW);
    glutAddMenuEntry("Magenta", C_MAGENTA);
    glutAddMenuEntry("Cyan", C_CYAN);

    int menu_id = glutCreateMenu(Processor::menuEvents);
    glutAddMenuEntry("Clear", CLEAR);
    glutAddSubMenu("Pick color", color_menu);
    glutAddMenuEntry("Pick shape", PICK_SHAPE);
    glutAddMenuEntry("Delete picked shape", DELETE_SHAPE);
    glutAddMenuEntry("Line", LINE);
    glutAddSubMenu("Triangle", triangle_menu);
    glutAddSubMenu("Quadrilateral", quad_menu);
    glutAddSubMenu("Oval", oval_menu);
    glutAddSubMenu("Regular Polygon", re_poly_menu);
    glutAddSubMenu("Other shapes", other_menu);
    glutAddSubMenu("Math Symbols", ope_menu);

    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Processor::mousePressed(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!isDrawOption(currentDrawOption)) {
            return;
        }

        isDrawing = true;
        switch (currentDrawOption) {
            case LINE:
                newShape = new Line(Point(x, y), Point(x, y), pickingColor);
                break;
            case RECTANGLE:
                newShape = new Rectangle(Point(x, y), Point(x, y), pickingColor);
                break;
            case SQUARE:
                newShape = new Square(Point(x, y), Point(x, y), pickingColor);
                break;
            case EQ_TRIANGLE:
                newShape = new EquilTriangle(Point(x, y), Point(x, y), pickingColor);
                break;
            case ISOR_TRIANGLE:
                newShape = new IsosRightTriangle(Point(x, y), Point(x, y), pickingColor);
                break;
            case CIRCLE:
                newShape = new Circle(Point(x, y), Point(x, y), pickingColor);
                break;
            case ELLIPSE:
                newShape = new Ellipse(Point(x, y), Point(x, y), pickingColor);
                break;
            case PENTAGON:
                newShape = new Pentagon(Point(x, y), Point(x, y), pickingColor);
                break;
            case HEXAGON:
                newShape = new Hexagon(Point(x, y), Point(x, y), pickingColor);
                break;
            case ARROW:
                newShape = new Arrow(Point(x, y), Point(x, y), pickingColor);
                break;
            case STAR:
                newShape = new Star(Point(x, y), Point(x, y), pickingColor);
                break;
            case ADD:
                newShape = new Add(Point(x, y), Point(x, y), pickingColor);
                break;
            case MINUS:
                newShape = new Minus(Point(x, y), Point(x, y), pickingColor);
                break;
            case TIMES:
                newShape = new Times(Point(x, y), Point(x, y), pickingColor);
                break;
            case DIVIDE:
                newShape = new Divide(Point(x, y), Point(x, y), pickingColor);
                break;
            default:
                break;
        }
        if (newShape) {
            storage.addShape(newShape);
            // shouldRedraw = true;
            glutPostRedisplay();
        }
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // Deselect the selecting shape (if any)
        if (selectingShape) {
            selectingShape->setSelecting(false);
            selectingShape = nullptr;
        }
        
        //////////////////////////////////////////////////////////////
        // Pick a shape for filling color
        if (isSelecting) {      
            Cell cell = canvas.getCell(y, x);
            Shape* shape = storage.getShape(cell.getLayer());

            // If we click to a "valid" cell (not empty)
            if (shape != nullptr) {
                shape->setSelecting(true);
                selectingShape = shape;
                // shouldFillSelectingShape = false;   // after pick shape, we have to pick color to fill this shape
            } else {
                selectingShape = nullptr;
            }
            
            // shouldRedraw = false;
            glutPostRedisplay();
            return;
        }

        
        //////////////////////////////////////////////////////////////
        // Other drawing options
        if (!isDrawOption(currentDrawOption)) {
            return;
        }

        if (newShape) {
            newShape->setEnd(Point(x, y));
            newShape = nullptr;
            isDrawing = false;

            glutPostRedisplay();
        }
    }
}

void Processor::mouseMove(int x, int y) {
    if (!isDrawing)
       return;

    if (newShape) {
        newShape->setEnd(Point(x, y));
        glutPostRedisplay();
    }
}

void Processor::normalKeyPressed(unsigned char key, int x, int y) {
    if (!selectingShape)
        return;

    double angle = 0.0;
    double sxy = 0.0;
    // L, R, +, - key handlers
    switch (key) {    
        case '+':
            sxy = 1.1;
            break;
        case '-':
            sxy = 0.9;
            break;
        case 'l':
            angle = -1;
            break;
        case 'r':
            angle = 1;
            break;
        default:
            return;
    }

    if (angle != 0.0)
        selectingShape->rotate(angle);
    else
        selectingShape->scale(sxy, sxy);

    glutPostRedisplay();
}

void Processor::specialKeyPressed(int key, int x, int y) {
    if (!selectingShape)
        return;

    // Up, down, left, right arrow key handlers
    double dx = 0.0, dy = 0.0;
    switch (key) {
        case GLUT_KEY_LEFT:
            dx = -1;
            break;
        case GLUT_KEY_RIGHT:
            dx = 1;
            break;
        case GLUT_KEY_UP:
            dy = -1;
            break;
        case GLUT_KEY_DOWN:
            dy = 1;
            break;
        default:
            return;
    }

    selectingShape->translate(dx, dy);
    glutPostRedisplay();
}


void Processor::display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (option == CLEAR) {
        glFinish();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    canvas.clear();
    storage.draw(canvas);
    glFlush();
}
