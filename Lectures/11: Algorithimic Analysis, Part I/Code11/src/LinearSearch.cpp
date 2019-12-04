/* File: LinearSearch.cpp
 *
 * A program to clock the speed of linear search.
 */

#include <iostream>
#include <ctime>
#include <string>
#include "console.h"
using namespace std;

/* How many trials of linear search to run. */
const int kNumTrials = 5000000;

bool linearSearch(const string& str, char ch) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ch) {
            return true;
        }
    }
    return false;
}

int main() {
    cout << "Starting..." << endl;
    clock_t start = clock();

    string source = "This string will be searched for 'x'";
    for (int i = 0; i < kNumTrials; i++) {
        linearSearch(source, 'x');
    }

    cout << "Program took " << (double(clock() - start) / CLOCKS_PER_SEC)
         << " seconds to complete." << endl;

    return 0;
}
