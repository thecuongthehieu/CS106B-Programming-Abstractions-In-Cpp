/*************************************************************
 * File: SinglyLinkedListPQueue.cpp
 *
 * Implementation file for the SinglyLinkedListPriorityQueue
 * class.
 */
 
#include "SinglyLinkedListPQueue.h"
#include "error.h"
using namespace std;



SinglyLinkedListPriorityQueue::SinglyLinkedListPriorityQueue() {
	// TODO: Fill this in!
    head = nullptr;
}

SinglyLinkedListPriorityQueue::~SinglyLinkedListPriorityQueue() {
	// TODO: Fill this in!
    while (!isEmpty()) {
        (void) dequeueMin();
    }
}

int SinglyLinkedListPriorityQueue::size() const {
	// TODO: Fill this in!
	
    return numElems;
}

bool SinglyLinkedListPriorityQueue::isEmpty() const {
	// TODO: Fill this in!
	
    return head == nullptr;
}

void SinglyLinkedListPriorityQueue::enqueue(const string& value) {
	// TODO: Fill this in!
    if (isEmpty()) {
        Cell* newCell = new Cell;
        newCell->value = value;
        newCell->next = head;
        head = newCell;
    } else {
        Cell* currentCell = head;
        if (currentCell->value > value) {
            Cell* newCell = new Cell;
            newCell->value = value;
            newCell->next = head;
            head = newCell;
        } else {
            Cell* beforeCell = currentCell;
            currentCell = currentCell->next;
            while (currentCell != nullptr) {
                if (currentCell->value > value)
                    break;
                beforeCell = currentCell;
                currentCell = currentCell->next;
            }
            Cell* newCell = new Cell;
            newCell->value = value;
            newCell->next = beforeCell->next;
            beforeCell->next = newCell;
        }

    }
    ++numElems;

}

string SinglyLinkedListPriorityQueue::peek() const {
	// TODO: Fill this in!
    if (isEmpty())
        error("This queue is empty! ");
    else
        return head->value;
}

string SinglyLinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
    if (isEmpty())
        error("This queue is empty! ");

    string firstValue = peek();
    Cell* next = new Cell;
    next = head->next;
    delete head;
    head = next;

    --numElems;

    return firstValue;
}

