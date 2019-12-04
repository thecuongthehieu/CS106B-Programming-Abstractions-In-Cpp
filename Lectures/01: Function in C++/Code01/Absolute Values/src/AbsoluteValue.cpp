#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Prototype the absoluteValueOf function so that we can call it before
 * it's defined.
 */
int absoluteValueOf(int n);

int main() {
    int value = getInteger("Please good sir or madam, permit me to collect from you, one integer. Pray tell: ");
    cout << "|" << value << "| = " << absoluteValueOf(value) << endl;
    return 0;
}

/**
 * Computes the absolute value of the input.
 *
 * @param n A number n.
 * @return |n|.
 */
int absoluteValueOf(int n) {
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}
