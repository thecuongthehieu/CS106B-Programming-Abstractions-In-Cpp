/*
 * File: gparking.h
 * --------------
 * This file defines the interface for the graphical parking functions.
 */

#ifndef _ghanoi_h
#define _ghanoi_h

#include "gwindow.h"

/*
 * Function: initParkingDisplay
 * Usage: initParkingDisplay(n);
 * -------------------------------
 * Initializes the graphics window and draws the starting configuration
 * for a road of length n.
 */

void initParkingDisplay(double n);

/*
 * Function: placeCar
 * Usage: placeCar(x);
 * -----------------------------------------------
 * Places a car at the specified position.
 */

void drawCarAt(double x);

/*
 * Function: removeAllCars
 * Usage: removeAllCars();
 * -----------------------------------------------
 * Removes all cars from the display.
 */
void removeAllCars();

/*
 * Function: displayAverage
 * Usage: displayAverage(averageCars);
 * -----------------------------------------------
 * Displays the specified number as the average
 * number of cars that have parked so far.
 */
void displayAverage(double averageCars);

#endif
