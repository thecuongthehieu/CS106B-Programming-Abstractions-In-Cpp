/* File: cell-towers.cpp
 *
 * A program that determines the maximum population that can be covered
 * by purchasing cell towers with a single transmitting frequency.
 */
#include <iostream>
#include <algorithm>
#include "vector.h"
#include "console.h"
using namespace std;

/**
 * Given a Vector<int>, returns a new Vector formed by removing the
 * first element of that Vector.
 *
 * This function takes its argument by value because it has to make
 * a copy of the Vector anyway, and that's as good a spot as any to
 * do it.
 *
 * @param v The input vector
 * @return A vector formed by dropping the first element
 */
Vector<int> tailOf(Vector<int> v) {
    v.remove(0);
    return v;
}

/**
 * Given a list of populations of cities on a linear highway,
 * returns the maximum number of people you can cover with
 * cell service, subject to the restriction that you can't
 * build cell towers in two adjacent cities.
 *
 * @param populations The populations of the cities on the highway.
 * @return The maximum number of people you can cover.
 */
int bestCoverageFor(const Vector<int>& populations) {
    /* Base case 1: If there are no cities, you can't cover anyone! */
    if (populations.size() == 0) {
        return 0;
    }
    /* Base case 2: If there's one city, cover it! */
    else if (populations.size() == 1) {
        return populations[0];
    }
    /* Recursive step. */
    else {
        Vector<int> allButFirst    = tailOf(populations);
        Vector<int> allButFirstTwo = tailOf(allButFirst);

        /* Option 1: Cover the first city. Then you can't cover the
         * second city, and should do whatever you can to maximize the
         * remaining cities.
         */
        int withFirst    = populations[0] + bestCoverageFor(allButFirstTwo);

        /* Option 2: Skip the first city. Then maximize everything
         * that's left.
         */
        int withoutFirst = bestCoverageFor(allButFirst);

        /* Take the better of the two options! */
        return max(withFirst, withoutFirst);
    }
}

/**
 * Given a list of cities, returns the total population of those
 * cities.
 *
 * @param populations The populations of the cities.
 * @return The total population.
 */
int populationOf(const Vector<int>& populations) {
    int result = 0;
    for (int cityPop: populations) {
        result += cityPop;
    }
    return result;
}

int main() {
	Vector<int> populations;
    populations += 137, 42, 95, 272, 52;

    cout << "Total population is " << populationOf(populations) << endl;
    cout << "Best coverage is    " << bestCoverageFor(populations) << endl;

	return 0;
}


