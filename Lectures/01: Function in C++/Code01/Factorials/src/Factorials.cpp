/* File: Factorials.cpp
 *
 * A program that computes n!.
 */

#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

int factorial(int n);

int main() {
    int value = getInteger("Give number me now: ");
    cout << value << "! = " << factorial(value) << endl;
    return 0;
}

/**
 * Returns n!, the number n * (n - 1) * ... * 1.
 *
 * @param n A number n, which must be nonnegative.
 * @return n!.
 */
int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}
