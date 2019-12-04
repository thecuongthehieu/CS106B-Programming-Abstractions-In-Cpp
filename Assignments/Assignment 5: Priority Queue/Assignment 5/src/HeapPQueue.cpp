/*************************************************************
 * File: HeapPQueue.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "HeapPQueue.h"
#include "error.h"
#include <algorithm>

using namespace std;

const int kInitialSize = 4;

HeapPriorityQueue::HeapPriorityQueue() {
	// TODO: Fill this in!
    logicalSize = 0;
    allocatedSize = kInitialSize;
    elems = new string[allocatedSize + 1];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	// TODO: Fill this in!
    delete[] elems;
}

int HeapPriorityQueue::size() const {
	// TODO: Fill this in!
	
    return logicalSize;
}

bool HeapPriorityQueue::isEmpty() const {
	// TODO: Fill this in!
	
    return size() == 0;
}

void HeapPriorityQueue::grow() {
    allocatedSize *= 2;
    string* newElems = new string[allocatedSize + 1];
    for (int i = 1; i <= logicalSize; ++i)
        newElems[i] = elems[i];
    delete[] elems;
    elems = newElems;
}

void HeapPriorityQueue::enqueue(const string& value) {
	// TODO: Fill this in!
    if (logicalSize == allocatedSize)
        grow();
    elems[logicalSize + 1] = value;
    ++logicalSize;

    int id = logicalSize;
    while (elems[id / 2] > elems[id]) {
        swap(elems[id / 2], elems[id]);
        id /= 2;
    }

}

string HeapPriorityQueue::peek() const {
	// TODO: Fill this in!
    if (isEmpty())
        error("This queue is empty! ");

    return elems[1];
}

string HeapPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
    if (isEmpty())
        error("This queue is empty! ");

    string root = peek();

    swap(elems[1], elems[logicalSize]);
    --logicalSize;

    int id = 1;

    while (2 * id <= logicalSize || 2 * id + 1 <= logicalSize) {
        if (2 * id == logicalSize) {
            if (elems[id] > elems[2 * id]) {
                swap(elems[id], elems[2 * id]);
            }
            break;
        } else {
            if (elems[id] <= elems[2 * id] && elems[id] <= elems[2 * id + 1])
                break;
            else if (elems[2 * id] < elems[2 * id + 1]) {
                swap(elems[id], elems[2 * id]);
                id *= 2;
            } else {
                swap(elems[id], elems[2 * id + 1]);
                id = 2 * id + 1;
            }
        }
    }

    return root;
}

