/* File: subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

Set<Set<int>> subsetsOf(const Set<int>& masterSet);

int main() {
    Set<int> masterSet = {1, 2, 3, 4, 5};
	
    for (Set<int> subset: subsetsOf(masterSet)) {
		cout << subset << endl;
	}

    return 0;
}

Set<Set<int>> subsetsOf(const Set<int>& masterSet) {
    /* Base case: the only subset of the empty set is the empty set itself. */
    if (masterSet.isEmpty()) {
        return { {} }; // Set containing the empty set.
    }
    /* Recursive case: fix an element, remove it, and generate subsets of what remains. */
    else {
        int elem = masterSet.first();

        Set<Set<int>> result;

        /* List the subsets of a smaller set formed by pulling out some element. */
        for (Set<int> subset: subsetsOf(masterSet - elem)) {
            /* For each of those subsets, make two copies. Keep one copy unmodified,
             * then add back the removed element into the other.
             */
            result += subset;
            result += subset + elem;
        }

        return result;
    }
}

