/*********************************************************
 * File: OurStack.h
 *
 * A class representing a stack that holds integers.
 */
#ifndef OurStack_Included
#define OurStack_Included

class OurStack {
public:
    OurStack();
    ~OurStack();

    void push(int value);
    int  pop();
    int  peek() const;
	
    int size() const;
    bool isEmpty() const;

private:
    int* elems;
    int  allocatedSize;
    int  logicalSize;
};


#endif
