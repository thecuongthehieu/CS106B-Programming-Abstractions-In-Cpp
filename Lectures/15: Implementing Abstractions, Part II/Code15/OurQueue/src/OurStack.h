/*********************************************************
 * File: OurStack.h
 *
 * A class representing a stack that holds integers.
 */
#ifndef OurStack_Included
#define OurStack_Included

class OurStack {
public:
	/* Constructor initializes the fields to reasonable values. */
	OurStack();
	
	/* Destructor cleans up all allocated memory. */
	~OurStack();

	void push(int value);
	int pop();
    int peek() const;
	
    bool isEmpty() const;
    int size() const;

private:
    int  allocatedSize; // How much space is allocated in our array.
    int  logicalSize;   // How many elements are logically in the array.
    int* elems;         // The actual array of elements.
	
	void grow();
};


#endif
