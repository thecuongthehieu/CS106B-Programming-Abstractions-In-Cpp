/* File: fun-with-strings.cpp
 *
 * A program for playing around with C++ strings!
 */
#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "console.h"
using namespace std;

string reverse(string input);

int main() {
    ifstream file("dictionary.txt");

    /* Find and display all the palindromes in English. */
    string line;
    while (getline(file, line)) {
        if (line == reverse(line)) {
            cout << line << endl;
        }
    }

    return 0;
}

/* Returns the reverse of the argument. */
string reverse(string input) {
    /* The reverse of the empty string is the empty string itself. */
    if (input == "") {
        return "";
    } else {
        /* Otherwise, reverse all but the first character, then tack on
         * the first character.
         */
        return reverse(input.substr(1)) + input[0];
    }
}

