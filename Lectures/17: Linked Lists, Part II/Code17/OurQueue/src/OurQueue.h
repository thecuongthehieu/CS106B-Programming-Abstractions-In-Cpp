/*********************************************************
 * File: OurQueue.h
 *
 * A class representing a Queue that holds integers.
 */
#ifndef OurQueue_Included
#define OurQueue_Included

class OurQueue {
public:
    OurQueue();
    ~OurQueue();

    void enqueue(int value);
    int dequeue();
    int peek() const;

    bool isEmpty() const;
    int size() const;

private:
    struct Cell {
        int value;
        Cell* next;
    };

    Cell* head;
    Cell* tail;

    /* We didn't cover this in class, but in order to make it easy (O(1)) to determine
     * how many elements there are in the list, we're going to cache the value here.
     *
     * You may notice we're initializing the value to zero here. We could also initialize
     * head and tail to nullptr here in the header file as well. To show off both ways of
     * initializing things - both in the class body and via constructors - I've opted not
     * to do that here.
     */
    int numElems = 0;
};

#endif
