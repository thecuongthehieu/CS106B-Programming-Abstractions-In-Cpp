/*
 * File: gparking.cpp
 * ----------------
 * This file implements the graphical parking functions.
 */

#include <iostream>
#include <string>
#include <memory> // For unique_ptr
#include "error.h"
#include "ParkingGraphics.h"
#include "gobjects.h"
#include "gwindow.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

/* Size of the window. */
const double kWindowWidth  = 800;
const double kWindowHeight = 400;

/* Amount to pause between iterations. */
const double kPauseTime = 500;

/* Max width we can use, which is picked so that we can actually see everything. */
const double kMaxWidth = 40;

/* Constants purely for the car image. */
const double kCarHeightOverWidth       = 5.0 / 7.0;
const double kWheelWidthFraction       = 2.0 / 7.0;
const double kWheelHeightFraction      = 0.5 / 5.0;
const double kBodyStartYFraction       = 0.5 / 5.0;
const double kBodyEndYFraction         = 4.5 / 5.0;
const double kWindshieldStartXFraction = 5.3 / 7.0;
const double kWindshieldEndXFraction   = 6.7 / 7.0;
const double kWindshieldStartYFraction = 1.1 / 5.0;
const double kWindshieldEndYFraction   = 3.9 / 5.0;

const string kWheelColor      = "#404040";
const string kWindshieldColor = "#80FFFF";

/* To be nice and pretty, let's use one of many different car colors. */
const int kNumCarColors = 15;
const string kCarColors[] = {
    "#FF0000", "#FF8000", "#FFFF00", "#00FF00", "#0000FF", "#FF00FF", "#FFFFFF", "#000000", "#808080",
	"#080000", "#080400", "#080800", "#008000", "#000080", "#800080"
};

/* Constants defining the color and shape of the road. */
const string kRoadColor   = "#202020";
const string kRoadStripeColor = "#FFA020";

const double kRoadStripeWidth = 20;
const double kRoadStripeHeight = 7;
const double kRoadStripeSpacing = 15;

static struct ParkingGraphics {
    unique_ptr<GWindow> window;
	
	/* The logical width of the curb. */
	double width;
	
	/* As an optimization, we preload the car image multiple times and
	 * resize them appropriately.
	 */
	Vector<GObject*> cars;
	
	/* Total number of cars that we have used so far. */
	int numCarsUsed;
	
	/* The amount of vertical space we have to work with for the road. */
	double verticalSpace;
	
	/* The label displaying the average number of cars parked so far. */
	GLabel* display;
} theGraphics;

/* Helpful graphics routines. */
GCompound* createCar();
void drawRoad();
double carWidth();
double carHeight();


/* Initializes the display. */
void initParkingDisplay(double width) {	
	if (width <= 0) {
		error("Sorry, but we need a nonzero curb width.");
	}
	if (width > kMaxWidth) {
		error("Sorry, but that width is too large to display.");
	}

	/* Create a new window to work with. */
    theGraphics.window.reset(new GWindow(kWindowWidth, kWindowHeight));
	
	/* Store the logical width for later use. */
    theGraphics.width = width;
	
	/* Create and add the label that reports the average. */
    theGraphics.display = new GLabel("");
    theGraphics.display->setFont("DejaVuSerif-24-BOLD");
    theGraphics.display->setLocation(0, theGraphics.window->getHeight() - theGraphics.display->getFontDescent());
    theGraphics.window->add(theGraphics.display);
	
	/* Determine vertical space by backing off the height of the label from the height of
	 * the window.
	 */
    theGraphics.verticalSpace = theGraphics.display->getY() - theGraphics.display->getFontAscent();
	
	/* Load all the car images. */
	int maxCarsPossible = int(width + 0.5);
	for (int i = 0; i < maxCarsPossible; i++) {
        theGraphics.cars += createCar();
	}
	
	/* Set up the road. */
	drawRoad();
}

/* Creates a filled GRect of the given color and position. */
GRect* makeFilledRect(double x, double y, double width, double height, string color, bool hasBorder = false) {
	GRect* result = new GRect(x, y, width, height);
	result->setFilled(true);
	if (hasBorder) {
		result->setFillColor(color);
	} else {
		result->setColor(color);
	}
	return result;
}

void drawRoad() {
	/* Fill a giant rectangle for the background. */
    theGraphics.window->add(makeFilledRect(0, 0, theGraphics.window->getWidth(), theGraphics.verticalSpace, kRoadColor));
	
	/* Fill stripes running down the middle. */
    double middleY = theGraphics.verticalSpace / 2.0;
	
    for (double x = 0; x < theGraphics.window->getWidth(); x += kRoadStripeWidth + kRoadStripeSpacing) {
		GRect* r = makeFilledRect(x, middleY - kRoadStripeHeight / 2.0, kRoadStripeWidth, kRoadStripeHeight, kRoadStripeColor);
        theGraphics.window->add(r);
	}
}

/* Returns the width that one car would occupy given the size of the curb. */
double carWidth() {
    return theGraphics.window->getWidth() / theGraphics.width;
}

/* Returns the height that one car would occupy given the size of the curb. */
double carHeight() {
	return kCarHeightOverWidth * carWidth();
}

/* Creates an image of a car and resizes it appropriately. */
GCompound* createCar() {
	/* The next car color to use. */
	static int sCarColor = 0;

	GCompound* result = new GCompound();

	/* Compute dimensions. */
	const double kCarWidth  = carWidth();
	const double kCarHeight = carHeight();
	
	/* Create the tires. */
	const double kTireWidth  = kWheelWidthFraction * kCarWidth;
	const double kTireHeight = kWheelHeightFraction * kCarHeight;
	result->add(makeFilledRect(0, 0, kTireWidth, kTireHeight, kWheelColor));
	result->add(makeFilledRect(0, kCarHeight - kTireHeight, kTireWidth, kTireHeight, kWheelColor));
	result->add(makeFilledRect(kCarWidth - kTireWidth, kCarHeight - kTireHeight, kTireWidth, kTireHeight, kWheelColor));
	result->add(makeFilledRect(kCarWidth - kTireWidth, 0, kTireWidth, kTireHeight, kWheelColor));
	
	/* Create the body. */
	const double kBodyY0 = kBodyStartYFraction * kCarHeight;
	const double kBodyY1 = kBodyEndYFraction * kCarHeight;
	result->add(makeFilledRect(0, kBodyY0, kCarWidth, kBodyY1 - kBodyY0,
	                           kCarColors[sCarColor++ % kNumCarColors], true));
	
	/* Create the windshield. */
	const double kWindX0 = kWindshieldStartXFraction * kCarWidth;
	const double kWindX1 = kWindshieldEndXFraction * kCarWidth;
	const double kWindY0 = kWindshieldStartYFraction * kCarHeight;
	const double kWindY1 = kWindshieldEndYFraction * kCarHeight;
	result->add(makeFilledRect(kWindX0, kWindY0, kWindX1 - kWindX0, kWindY1 - kWindY0, kWindshieldColor));
	
	return result;
}

void drawCarAt(double logicalX) {
    GObject* toAdd = theGraphics.cars[theGraphics.numCarsUsed++];
	
	/* Scale the x based on the width of one car, then position the car at the
	 * bottom of the road.
	 */
	double x = logicalX * carWidth();
    double y = theGraphics.verticalSpace - carHeight();
	
	toAdd->setLocation(x, y);
    theGraphics.window->add(toAdd);
}

/*
 * Function: removeAllCars
 * Usage: removeAllCars();
 * -----------------------------------------------
 * Removes all cars from the display.
 */
void removeAllCars() {
    for (int i = 0; i < theGraphics.numCarsUsed; i++) {
        theGraphics.window->remove(theGraphics.cars[i]);
	}
    theGraphics.numCarsUsed = 0;
}

/*
 * Function: displayAverage
 * Usage: displayAverage(averageCars);
 * -----------------------------------------------
 * Displays the specified number as the average
 * number of cars that have parked so far.
 */
void displayAverage(double averageCars) {
    theGraphics.display->setLabel("Average number of cars: " + realToString(averageCars));
	pause(kPauseTime);
}
