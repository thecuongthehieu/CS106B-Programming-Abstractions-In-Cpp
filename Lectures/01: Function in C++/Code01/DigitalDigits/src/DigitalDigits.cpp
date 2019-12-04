/* File: DigitalDigits.cpp
 *
 * A program that explores properties of digits of
 * numbers!
 */
#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Prototypes so that we can call these functions later on. */
int sumOfDigitsOf(int n);
int digitalRootOf(int n);

int main() {
    while (true) {
        int val = getInteger("Number please: ");
        cout << "The sum of the digits is " << sumOfDigitsOf(val) << endl;
    }
    return 0;
}

/**
 * Returns the sum of the digits of the input number.
 * 
 * @param n An input, which must be nonnegative.
 * @return The sum of the digits of the number n.
 */
int sumOfDigitsOf(int n) {
    if (n < 10) {
        return n;
    } else {
        return sumOfDigitsOf(n / 10) + (n % 10);
    }
}

/**
 * Returns the digital root of the input, the number formed by
 * repeatedly adding the digits of n until we're down to a
 * single digit.
 *
 * @param n A number n, which must be nonnegative.
 * @return The digital root of n.
 */
int digitalRootOf(int n) {
    while (n >= 10) {
        n = sumOfDigitsOf(n);
    }
    return n;
}
