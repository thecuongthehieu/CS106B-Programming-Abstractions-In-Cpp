#include <iostream>
#include "console.h"
#include "RandomBag.h"
using namespace std;

void printBagStats(const RandomBag& bag) {
    cout << "The random bag contains " << bag.size() << " elements." << endl;
}

int main() {
    /* Fill a random bag with some values. */
    RandomBag bag;
    for (int i = 0; i < 10; i++) {
        bag.add(i + 1);
    }
    printBagStats(bag);

    /* Remove them all in random order. */
    while (!bag.isEmpty()) {
        cout << bag.removeRandom() << " ";
    }
    cout << endl;

    return 0;
}
