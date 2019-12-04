/*
 * File: ParkingRandomly.cpp
 * ---------------
 * A program that attempts to determine how many cars can park on a curb
 * of a certain length, based on certain assumptions on how cars can park.
 */

#include <iostream>
#include "random.h"
#include "ParkingGraphics.h" // Routines for displaying the cars
using namespace std;

/* Constant controlling the size of the road. */
const double kRoadLength = 10;

/* Simulates one iteration of parking randomly, returning
 * how many cars could be placed.
 */
int parkRandomly(double start, double end);

int main() {
	initParkingDisplay(kRoadLength);

    /* Count up how many trials we've done and how many total cars have
     * been placed.
	 */
	int numTrials = 0;
	int numTotalCars = 0;
	
	while (true) {
		/* Clear the display. */
		removeAllCars();
		numTrials++;
		
		/* Simulate one iteration of parking randomly. */
		numTotalCars += parkRandomly(0, kRoadLength);
		
		/* Update the display to show the average number of cars
		 * based on the trials we've done so far.
		 */
		displayAverage(double(numTotalCars) / numTrials);
	}
}

int parkRandomly(double start, double end) {
    if (end - start < 1.0) {
        return 0;
    } else {
        double position = randomReal(start, end - 1.0);
        drawCarAt(position);

        return 1 + parkRandomly(start, position) + parkRandomly(position + 1.0, end);
    }
}







