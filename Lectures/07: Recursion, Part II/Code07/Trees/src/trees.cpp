/*
 * File: Trees.cpp
 * ---------------
 * A program that generates trees using recursion!
 */

#include <iostream>
#include <string>
#include "random.h"
#include "gwindow.h"
#include "gobjects.h"
#include "gevents.h"
using namespace std;

const double kWindowWidth = 800;
const double kWindowHeight = 600;

const int kMinChildren = 2;
const int kMaxChildren = 8;

const double kMinAngle = -50;
const double kMaxAngle = +50;

const int kTreeOrder = 8;

void drawTreeRec(GWindow& window,
                 double x, double y,
                 double length,
                 double angle,
                 int order) {
    if (order == 0) return;

    GPoint endpoint = window.drawPolarLine(x, y, length / 2, angle);

    int numChildren = randomInteger(kMinChildren, kMaxChildren);

    for (int i = 0; i < numChildren; i++) {
        drawTreeRec(window, endpoint.getX(), endpoint.getY(), length / 2,
                    angle + randomReal(kMinAngle, kMaxAngle), order - 1);
    }
}

void drawTree(GWindow& window, double x, double y, double length) {
    drawTreeRec(window, x, y, length, 90, kTreeOrder);
}

/* Main program */
int main() {
	GWindow window(kWindowWidth, kWindowHeight);
    drawTree(window, window.getWidth() / 2, window.getHeight(), window.getHeight());
    return 0;
}






