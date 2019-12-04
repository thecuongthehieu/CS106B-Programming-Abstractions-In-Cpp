/*************************************************************
 * File: DoublyLinkedListPQueue.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "DoublyLinkedListPQueue.h"
#include "error.h"
using namespace std;

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    // TODO: Fill this in!
    first = nullptr;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
}

int DoublyLinkedListPriorityQueue::size() const {
	// TODO: Fill this in!
	
    return numElems;
}

bool DoublyLinkedListPriorityQueue::isEmpty() const {
	// TODO: Fill this in!
	
    return first == nullptr;
}

void DoublyLinkedListPriorityQueue::enqueue(const string& value) {
	// TODO: Fill this in!
    if (isEmpty()) {
        Cell* newCell = new Cell;
        newCell->value = value;
        newCell->next = first;
        newCell->previous = nullptr;
        first = newCell;
    } else {
        Cell* newCell = new Cell;
        newCell->value = value;
        newCell->next = first;
        newCell->previous = nullptr;
        first->previous = newCell;
        first = newCell;
    }
    ++numElems;
}

string DoublyLinkedListPriorityQueue::peek() const {
	// TODO: Fill this in!
    if (isEmpty())
        error("This queue is empty! ");
    Cell* tmp = first;
    string minVal = tmp->value;

    while (tmp != nullptr) {
        if (tmp->value < minVal)
            minVal = tmp->value;
        tmp = tmp->next;
    }

    return minVal;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
    if (isEmpty())
        error("This queue is empty! ");

    string minVal = peek();
    Cell* tmp = first;
    while (tmp->next != nullptr) {
        if (tmp->value == minVal)
            break;
        tmp = tmp->next;
    }

    if (tmp->next == nullptr && tmp->previous == nullptr) {
        first = nullptr;
    } else if (tmp->next == nullptr) {
        tmp->previous->next = nullptr;
    } else if (tmp->previous == nullptr) {
        tmp->next->previous = nullptr;
        first = tmp->next;
    } else {
        tmp->previous->next = tmp->next;
        tmp->next->previous = tmp->previous;
    }

    delete tmp;
    --numElems;

    return minVal;
}

