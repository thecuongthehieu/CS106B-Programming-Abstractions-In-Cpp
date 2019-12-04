/*****************************************************
 * File: Main.cpp
 *
 * A program to run simple tests on our custom Queue.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "OurQueue.h"
#include "simpio.h"
#include "random.h"
#include "console.h"
using namespace std;

const int kNumElems = 8;

void runSimpleTests() {
    OurQueue queue;

    /* Load the queue with random values. */
    cout << "Enqueuing elements into the queue:" << endl;
    for (int i = 0; i < kNumElems; i++) {
        int value = randomInteger(0, 1000);
        cout << setw(6) << value;
        queue.enqueue(value);
    }
    cout << endl;

    /* See what those values are. */
    cout << "Dequeuing elements from the queue:" << endl;
    while (!queue.isEmpty()) {
        cout << setw(6) << queue.dequeue();
    }
    cout << endl;
}

void runTimeTests(int minSize, int maxSize, int stepSize) {
    for (int i = minSize; i <= maxSize; i += stepSize) {
        double startTime = clock();

        OurQueue queue;
        for (int elem = 0; elem < i; elem++) {
            queue.enqueue(elem);
        }

        for (int elem = 0; elem < i; elem++) {
            queue.dequeue();
        }

        double elapsed = (clock() - startTime) / double(CLOCKS_PER_SEC);
        cout << "Time for " << i << ": " << elapsed << "s" << endl;
    }

}

int main() {
    cout << "Welcome to the Queue Test Driver!" << endl;
    cout << "Please choose an option: " << endl;
    cout << "  1: Simple tests" << endl;
    cout << "  2: Easy time tests" << endl;
    cout << "  3: Hard time tests" << endl;
    cout << "  4: Call it a day" << endl;

    while (true) {
        int option = getInteger("Your choice: ");
        if (option == 1) runSimpleTests();
        else if (option == 2) runTimeTests(5000, 50000, 5000);
        else if (option == 3) runTimeTests(1000000, 10000000, 1000000);
        else if (option == 4) break;
        else cerr << "Sorry, I don't understand." << endl;
    }

    cout << "Have a nice day!" << endl;
    return 0;
}
