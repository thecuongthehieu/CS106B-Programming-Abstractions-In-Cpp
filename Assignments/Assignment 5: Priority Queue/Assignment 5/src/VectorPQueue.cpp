/*************************************************************
 * File: VectorPQueue.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "VectorPQueue.h"
#include "error.h"
using namespace std;

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() const {
	// TODO: Fill this in!
    cout << elems.size() << endl;
    return elems.size();
}

bool VectorPriorityQueue::isEmpty() const {
	// TODO: Fill this in!
    return elems.empty();
}

void VectorPriorityQueue::enqueue(const string& value) {
	// TODO: Fill this in!
    elems.push_back(value);
}

string VectorPriorityQueue::peek() const {
	// TODO: Fill this in!
    if (isEmpty())
        error("This Queue is empty!");
    std::string alphabetFirst = *elems.begin();
    for (int i = 0; i < elems.size(); ++i) {
        if (elems[i] < alphabetFirst)
            alphabetFirst = elems[i];
    }

    return alphabetFirst;
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!

    std::string alphabetFirst = peek();
    int id;
    for (int i = 0; i < elems.size(); ++i) {
        if (elems[i] == alphabetFirst)
            id = i;
    }

    elems.erase(elems.begin() + id);


    return alphabetFirst;
}

