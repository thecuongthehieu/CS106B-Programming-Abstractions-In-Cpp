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

/* Branching angle. */
const double kMinAngle = -60;
const double kMaxAngle = +60;

/* Number of branches at each tree. */
const int kMinBranchingFactor = 5;
const int kMaxBranchingFactor = 7;

/* Maximum level of the tree. */
const int kMaxLevel = 7;

/* Colors to use for drawing the tree */
const string kBranchColors[kMaxLevel + 1] = {
   "whoops!", // This is never used
   "#006000", // Leaves are green
   "#008000", // Below that is slightly brighter.
   "#00a000", // Below that is brighter green. Thanks, Bob Ross!
   "#904000", // Branches are mostly brown
   "#a05000",
   "#905000",
   "#984800",
};

void drawTree(GWindow& window, double x, double y, double length, double theta);

/* Main program */
int main() {
	GWindow window(kWindowWidth, kWindowHeight);
	drawTree(window, window.getWidth() / 2.0, window.getHeight(),
	         window.getHeight(), 90);
    GImage* image = new GImage("BobRoss.png");

    waitForClick();
    window.add(image, window.getWidth() - image->getWidth(), window.getHeight() - image->getHeight());
	return 0;
}

void recDrawTree(GWindow& window, double x, double y, double length, double theta, int order) {
	/* Drawing an order-0 tree is instantaneous. */
	if (order == 0) return;
	
	/* Draw the tree trunk and remember the endpoint. */
    window.setColor(kBranchColors[order]);
	GPoint endpoint = window.drawPolarLine(x, y, length / 2.0, theta);
	
	/* Determine how many child branches we should have. */
	int numChildren = randomInteger(kMinBranchingFactor, kMaxBranchingFactor);
	                                
	/* Recursively draw all child branches. */
	for (int i = 0; i < numChildren; i++) {
        recDrawTree(window,                                   // Draw in the same window,
                    endpoint.getX(), endpoint.getY(),         // at the end of the branch,
                    length / 2.0,                             // half as big as before,
                    theta + randomReal(kMinAngle, kMaxAngle), // rotated at a random angle, and
                    order - 1);                               // of slightly smaller order.
	}
}

void drawTree(GWindow& window, double x, double y, double length, double theta) {
	recDrawTree(window, x, y, length, theta, kMaxLevel);
}








