/*************************************************
 * File: LinkedLists.cpp
 *
 * Our very first program using Linked Lists! :-D
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Type: Cell
 *
 * A cell in a linked list.
 */
struct Cell {
	string value;
	Cell* next;
};

/* Reads in a list of values from the user and builds a linked list from them.
 * The list is in the reverse order in which the elements were added in.
 */
Cell* readList() {
    Cell* result = nullptr;

    while (true) {
        string line = getLine("Next entry? ");
        if (line == "") break;

        /* Create a new cell. */
        Cell* cell = new Cell;
        cell->value = line;

        /* Prepend it to the list. */
        cell->next = result;
        result = cell;
    }

    return result;
}

/* Recursively reads in a list of values from the user and builds a list out of them.
 * The elements will be in the order in which they were added.
 */
Cell* readListRec() {
    string line = getLine("Next entry? ");

    /* Base Case: If there's nothing to put in the list, return an empty list. */
    if (line == "") return nullptr;

    /* Recursive Step: Make a new cell with this value, then fill in the rest of
     * the list recursively.
     */
    Cell* result = new Cell;
    result->value = line;
    result->next = readListRec();
    return result;
}

/* Prints the contents of a linked list in order. */
void printList(Cell* list) {
    for (Cell* cell = list; cell != nullptr; cell = cell->next) {
        cout << cell->value << endl;
    }
}

/* Prints the contents of a linked list recursively. */
void printListRec(Cell* list) {
    /* Base Case: Empty list, nothing to print! */
    if (list == nullptr) return;

    /* Recursive Step: Print the first element, then the remaining ones. */
    cout << list->value << endl;
    printListRec(list->next);
}

int main() {
    Cell* list = readListRec();
    printListRec(list);

    // TODO: Deallocate all the memory we allocated so we don't have a leak!
    // We'll see how to do this on Wednesday.

    return 0;
}




