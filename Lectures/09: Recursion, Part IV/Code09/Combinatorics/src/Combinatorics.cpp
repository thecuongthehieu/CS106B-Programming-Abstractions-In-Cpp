/* File: Combinatorics.cpp
 *
 * Functions to list off all the combinations of characters
 * from a string.
 */
#include <iostream>
#include <string>
#include "console.h"
using namespace std;

void listCombinationsRec(const string& str, int k, const string& soFar) {
    /* Base case 1: If we've already chosen our k elements, we're done! */
    if (k == 0) {
        cout << soFar << endl;
    }
    /* Implicit base case 2: If we haven't chosen k elements, but there aren't any
     * more characters left, we're done.
     *
     * Fun exercise: make this code run faster by adding in a new base case that
     * also traps the case where there aren't enough elements to go around.
     */
    else if (str != "") {
        /* Recursive step: We either include the first element of the string, or
         * we exclude it.
         */
        listCombinationsRec(str.substr(1), k, soFar);            // Don't include first element
        listCombinationsRec(str.substr(1), k-1, soFar + str[0]); // Do include first element
    }
}

/**
 * Given a string and a number k, lists off all strings that can be formed by picking
 * k characters out of the string in the order in which they appear.
 *
 * @param str The string in question.
 * @param k The number k.
 */
void listCombinationsOf(const string& str, int k) {
    listCombinationsRec(str, k, "");
}

int main() {
    listCombinationsOf("abcd", 4);
    return 0;
}
