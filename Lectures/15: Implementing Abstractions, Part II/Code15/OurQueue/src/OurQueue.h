/*********************************************************
 * File: OurQueue.h
 *
 * A class representing a Queue that holds integers.
 */
#ifndef OurQueue_Included
#define OurQueue_Included

#include "OurStack.h"

class OurQueue {
public:
    void enqueue(int value);
    int dequeue();
    int peek();

    bool isEmpty() const;
    int size() const;

private:
    OurStack in, out;
};

/* You might have noticed that peek is no longer marked const.
 * This is because we may have to change the underlying two stacks
 * if the out stack is empty. If we mark peek const, then we can't
 * modify in or out, which is a problem.
 *
 * We can get around this by using a C++ keyword called "mutable."
 * A field marked mutable can be modified even inside of a const
 * member function. You should be very careful about using this
 * keyword - it's designed for cases like these where you have an
 * internal representation that appears to be unchanged in response
 * to an operation but actually has to move things around about.
 * The terms to look up are "bitwise const" (you don't change any
 * of the data members) and "semantically const" (you don't change
 * the observable state of the object.) If you're curious, here's
 * what this would look like:
 *
 * class OurQueue {
 * public:
 *     void enqueue(int value);
 *     int dequeue();
 *     int peek() const;
 *
 *     bool isEmpty() const;
 *     int size() const;
 *
 * private:
 *     mutable OurStack in, out;
 * };
 */


#endif
