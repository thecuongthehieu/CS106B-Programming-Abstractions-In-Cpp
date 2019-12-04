#include "OurQueue.h"
#include "error.h"

/* The queue is empty if both underlying stacks are empty. */
bool OurQueue::isEmpty() const {
	return in.isEmpty() && out.isEmpty();
}

/* The total number of elements is the sum of the number of elements
 * in each stack.
 */
int OurQueue::size() const {
	return in.size() + out.size();
}

/* Enqueuing something adds to the "in" stack. */
void OurQueue::enqueue(int value) {
	in.push(value);
}

/* Peeking requires the out stack to be nonempty. If it is
 * empty, transfer everything over from the in stack.
 */
int OurQueue::peek() {
    if (isEmpty()) {
        error("That which both is and is not.");
    }

	if (out.isEmpty()) {
		while (!in.isEmpty()) {
			out.push(in.pop());
		}
	}
	
	return out.peek();
}

/* We dequeue by taking elements out of the out stack. */
int OurQueue::dequeue() {
	int result = peek();
	out.pop();
	return result;
}
