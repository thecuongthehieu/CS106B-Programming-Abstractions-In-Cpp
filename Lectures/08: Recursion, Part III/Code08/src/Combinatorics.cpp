/* File: Combinatorics.cpp
 *
 * Functions to list off all subsets and permutations of a collection of elements.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/**
 * Given a set of integers, lists off all the subsets of that set.
 *
 * @param masterSet The set in question.
 */
void listSubsetsOf(const Set<int>& masterSet);

/**
 * Given a string, lists off all permutations of that string.
 *
 * @param str The string in question.
 */
void listPermutationsOf(const string& str);

int main() {
    listSubsetsOf({1, 2, 3, 4});
    listPermutationsOf("ibex");

    return 0;
}

void listSubsetsRec(const Set<int>& masterSet, const Set<int>& used) {
    /* Base case: If all decisions have been made, print out the consequences of
     * those decision.
     */
    if (masterSet.isEmpty()) {
        cout << used << endl;
    }
    /* Recursive case: Choose an element from the set, and explore what happens if we
     * do or do not use it.
     */
    else {
        int element = masterSet.first();

        listSubsetsRec(masterSet - element, used);           // Without
        listSubsetsRec(masterSet - element, used + element); // With
    }
}

void listSubsetsOf(const Set<int>& masterSet) {
    listSubsetsRec(masterSet, {});
}

void listPermutationsRec(const string& str, const string& soFar) {
    /* Base case: If all decisions have been made, print out the consequences of
     * those decisions.
     */
    if (str == "") {
        cout << soFar << endl;
    }
    /* Recursive case: For each possible character that could go at the front of the
     * string, put that character in the front and permute what's left.
     */
    else {
        for (int i = 0; i < str.length(); i++) {
            listPermutationsRec(str.substr(0, i) + str.substr(i + 1), // The string you get by removing character i
                                soFar + str[i]);                      // The prefix you form by appending character i
        }
    }
}

void listPermutationsOf(const string& str) {
    listPermutationsRec(str, "");
}
