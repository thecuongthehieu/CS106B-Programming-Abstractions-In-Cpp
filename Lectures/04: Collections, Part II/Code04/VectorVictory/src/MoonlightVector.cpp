/* File: MoonlightVector.cpp
 *
 * Some simple code to play around with vectors and parameter passing.
 */
#include <iostream>
#include <string>
#include "vector.h"
#include "console.h"
using namespace std;

void growUp(Vector<string>& characters);
void rollCredits(const Vector<string>& cast);

int main() {
    Vector<string> moonlight;
    moonlight += "Little", "Teresa", "Kevin";

    growUp(moonlight);
    rollCredits(moonlight);

    return 0;
}

/* This function takes its argument by reference, so any changes it
 * makes will stick back in main.
 */
void growUp(Vector<string>& characters) {
    characters += "Paula";
    characters[0] = "Chiron";
}

/* This function takes its argument by const reference, so it's not
 * permitted to change it.
 */
void rollCredits(const Vector<string>& cast) {
    cout << "Characters: ";
    for (string name: cast) {
        cout << name << " ";
    }
    cout << endl;
}

