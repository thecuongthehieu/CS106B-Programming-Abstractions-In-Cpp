/*****************************************************
 * File: SimpleTest.cpp
 *
 * A program to run simple tests on our custom Stack.
 */
#include <iostream>
#include "OurStack.h"
#include "simpio.h"
#include "random.h"
#include "console.h"
using namespace std;

const int kNumElems = 4;

int main() {
	OurStack stack;
	
	/* Load the stack with random values. */
    cout << "Pushing values onto the stack:" << endl;
    for (int i = 0; i < kNumElems; i++) {
		int value = randomInteger(0, 1000);
        cout << "  " << value << endl;
		stack.push(value);
	}

    cout << "Popping values from the stack: " << endl;
	
	/* See what those values are. */
	while (!stack.isEmpty()) {
        cout << "  " << stack.pop() << endl;
	}
	
	return 0;
}
