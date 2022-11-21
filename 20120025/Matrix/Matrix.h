#pragma once
#include <vector>
#include <cmath>
#include "../macros.h"
#include "../Shape/Point.h"
#include "../utils/logics.h"
#include <iostream>
using namespace std;

#define I_3x3 vector<vector<double>>{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}

class Matrix {
private:
    vector<vector<double>> Elements;

public:
    Matrix() {
        Elements = I_3x3;
    }

    Matrix(double m11, double m12, double m21, double m22, double m31, double m32) {
        Elements = {{m11, m12, 0}, {m21, m22, 0}, {m31, m32, 1}};
    }

public:
    double Get(int i, int j) {
        return Elements[i][j];
    }

    // Resets this Matrix to have the elements of the identity matrix.
    void Reset() {
        Elements = I_3x3;
    }

    // Inverts this Matrix, if it is invertible.
    void Invert() {
        if (Elements == I_3x3)
            return;

        double m11 = Elements[0][0];
        double m12 = Elements[0][1];
        double m13 = Elements[0][2];
        double m21 = Elements[1][0];
        double m22 = Elements[1][1];
        double m23 = Elements[1][2];
        double m31 = Elements[2][0];
        double m32 = Elements[2][1];
        double m33 = Elements[2][2];

        double D = (m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32) -
                   (m13 * m22 * m31 + m12 * m21 * m33 + m11 * m23 * m32);
        if (D == 0) {
            throw "The Affine Matrix is not invertible";
        }

        double invD = 1 / D;
        Elements[0][0] = (m22 * m33 - m23 * m32) * invD;
        Elements[0][1] = (m13 * m32 - m12 * m33) * invD;
        Elements[0][2] = (m12 * m23 - m13 * m22) * invD;
        Elements[1][0] = (m23 * m31 - m21 * m33) * invD;
        Elements[1][1] = (m11 * m33 - m13 * m31) * invD;
        Elements[1][2] = (m13 * m21 - m11 * m23) * invD;
        Elements[2][0] = (m21 * m32 - m22 * m31) * invD;
        Elements[2][1] = (m12 * m31 - m11 * m32) * invD;
        Elements[2][2] = (m11 * m22 - m12 * m21) * invD;
    }

    // Multiplies this Matrix by the matrix specified in the `other` parameter, by prepending the specified Matrix.
    void Multiply(Matrix other) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                double sum = 0;
                for (int k = 0; k < 3; k++) {
                    sum += Elements[i][k] * other.Elements[k][j];
                }
                Elements[i][j] = sum;
            }
        }
    }

    // Prepend to this Matrix a clockwise rotation, around the origin and by the specified angle (in degrees).
    void Rotate(double angle) {
        double radian = angle * PI / 180;
        double cos = std::cos(radian);
        double sin = std::sin(radian);

        Matrix newMatrix = Matrix();
        newMatrix.Elements[0][0] = cos;
        newMatrix.Elements[0][1] = -sin;
        newMatrix.Elements[1][0] = sin;
        newMatrix.Elements[1][1] = cos;

        Multiply(newMatrix);
    }

	
    // Applies the specified translation vector (offsetX and offsetY) to this Matrix by prepending the translation vector.
    void Translate (double offsetX, double offsetY) {
        Matrix newMatrix = Matrix();
        newMatrix.Elements[2][0] = offsetX;
        newMatrix.Elements[2][1] = offsetY;

        Multiply(newMatrix);
    }

    // Applies the specified shear vector to this Matrix by prepending the shear transformation.
    void Scale(double scaleX, double scaleY) {
        Matrix newMatrix = Matrix();
        newMatrix.Elements[0][0] = scaleX;
        newMatrix.Elements[1][1] = scaleY;

        Multiply(newMatrix);
    }

    // Applies the specified shear vector to this Matrix by prepending the shear transformation.
    void Shear(double shearX, double shearY) {
        Matrix newMatrix = Matrix();
        newMatrix.Elements[0][1] = shearX;
        newMatrix.Elements[1][0] = shearY;

        Multiply(newMatrix);
    }

    //  Applies the geometric transform represented by this Matrix to a specified array of points.
    Point TransformPoint(Point point) {
        if (Elements == I_3x3) {
            return point;
        }

        double x = point.x();
        double y = point.y();
        int newX = clip(round(Elements[0][0] * x + Elements[1][0] * y + Elements[2][0]), 0, WIN_WIDTH - 1);
        int newY = clip(round(Elements[0][1] * x + Elements[1][1] * y + Elements[2][1]), 0, WIN_HEIGHT - 1);

        return Point(newX, newY);
    }

    // Applies the geometric transform represented by this Matrix to a specified array of points.
    vector<Point> TransformPoints(vector<Point> points) {
        if (Elements == I_3x3) {
            return points;
        }

        vector<Point> newPoints;
        for (Point point : points) {
            newPoints.push_back(TransformPoint(point));
        }
        return newPoints;
    }
};