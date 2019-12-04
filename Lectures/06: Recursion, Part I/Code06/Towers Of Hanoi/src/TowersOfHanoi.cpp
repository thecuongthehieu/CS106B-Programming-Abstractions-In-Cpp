/*
 * File: TowersOfHanoi.cpp
 * ---------------
 * This program solves the Tower of Hanoi puzzle.
 */

#include <iostream>
#include "HanoiGraphics.h"    // Animation routines.
using namespace std;

/* Constants */

const int kNumDisks = 5;

/* Moves n disks from the start spindle to the destination spindle,
 * using the given spindle as a temporary.
 */
void moveTower(int n, char start, char finish, char temp);


int main() {
    initHanoiDisplay(kNumDisks);
    moveTower(kNumDisks, 'a', 'c', 'b');
	return 0;
}

/*
 * Function: moveTower
 * Usage: moveTower(n, start, finish, temp);
 * -----------------------------------------
 * Moves a tower of size n from the start spire to the finish
 * spire using the temp spire as the temporary repository.
 */

void moveTower(int n, char start, char finish, char temp) {
   if (n != 0) {
      moveTower(n - 1, start, temp, finish);
      moveSingleDisk(start, finish);
      moveTower(n - 1, temp, finish, start);
   }
}
