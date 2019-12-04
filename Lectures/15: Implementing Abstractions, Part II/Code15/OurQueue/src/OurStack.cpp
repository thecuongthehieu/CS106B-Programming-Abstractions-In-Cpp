#include "OurStack.h"
#include "error.h"

/* Constant controlling the default size of our stack. */
const int kInitialSize = 4;

/* Constructor initializes the fields of the stack to
 * appropriate defaults.
 */
OurStack::OurStack() {
    logicalSize = 0;
    allocatedSize = kInitialSize;
    elems = new int[allocatedSize];
}

/* Destructor cleans up memory allocated by the stack. */
OurStack::~OurStack() {
	delete[] elems;
}

int OurStack::size() const {
    return logicalSize;
}

bool OurStack::isEmpty() const {
	return size() == 0;
}

void OurStack::grow() {
    allocatedSize *= 2;
    int* newElems = new int[allocatedSize];
    for (int i = 0; i < logicalSize; i++) {
        newElems[i] = elems[i];
	}
	delete[] elems;
    elems = newElems;
}
void OurStack::push(int value) {
    if (allocatedSize == logicalSize) {
		grow();
	}
    elems[logicalSize] = value;
    logicalSize++;
}

int OurStack::peek() const {
	if (isEmpty()) {
		error("What is the sound of one hand clapping?");
	}

    return elems[logicalSize - 1];
}

int OurStack::pop() {
	int result = peek();
    logicalSize--;
	return result;
}



