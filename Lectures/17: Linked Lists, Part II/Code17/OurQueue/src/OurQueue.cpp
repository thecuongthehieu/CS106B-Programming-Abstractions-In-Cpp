#include "OurQueue.h"
#include "error.h"

/* Initially, the queue is empty and has no cells. */
OurQueue::OurQueue() {
    head = tail = nullptr;
}

/* To free our memory, we can just dequeue all the cells!
 * We could speed this up a bit by just using our traditional
 * "free all the memory" operation from class, but I like the
 * simplicity here and unless this ends up being a bottleneck it's
 * actually not that bad of an idea.
 */
OurQueue::~OurQueue() {
    while (!isEmpty()) {
        (void) dequeue(); // The (void) here means "discard the return value."
    }
}

/* Enqueuing an element appends it to the list. */
void OurQueue::enqueue(int value) {
    Cell* cell = new Cell;
    cell->value = value;
    cell->next = nullptr; // Goes on the end of the list

    if (isEmpty()) {
        head = tail = cell;
    } else {
        tail->next = cell;
        tail = cell;
    }

    /* Keep track of how many elements there are. */
    numElems++;
}

/* Looks at the front cell in the list. */
int OurQueue::peek() const {
    if (isEmpty()) {
        error("Thanks, Obama.");
    }
    return head->value;
}

/* Deallocates and removes the first element of the list. */
int OurQueue::dequeue() {
    int result = peek();

    Cell* next = head->next;
    delete head;
    head = next;

    /* Edge case: If the list is now empty, update the tail pointer. */
    if (head == nullptr) {
        tail = nullptr;
    }

    /* Remember that we just deleted a cell. */
    numElems--;

    return result;
}

/* There are a ton of ways we can implement this. */
bool OurQueue::isEmpty() const {
    return head == nullptr; // Or tail == nullptr. But why DON'T we do head == tail?
}

/* Use our cached value. */
int OurQueue::size() const {
    return numElems;
}
