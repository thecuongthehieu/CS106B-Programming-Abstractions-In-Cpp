/*****************************************************
 * File: Main.cpp
 *
 * A program to play around with our new hash set!
 */
#include <iostream>
#include "OurHashSet.h"
#include "console.h"
#include "simpio.h"
using namespace std;

int main() {
    OurHashSet set;
    set.add("calliope");
    set.add("polyhymnia");
    set.add("euterpe");
    set.add("terpsichore");
    set.add("urania");
    set.add("clio");
    set.add("erato");
    set.add("melpomene");
    set.add("thalia");

    while (true) {
        string name = getLine("What are you musing about? ");
        if (set.contains(name)) {
            cout << "Muse-ic to my ears!" << endl;
        } else {
            cout << "We are not a-mused." << endl;
        }
    }

    return 0;
}
