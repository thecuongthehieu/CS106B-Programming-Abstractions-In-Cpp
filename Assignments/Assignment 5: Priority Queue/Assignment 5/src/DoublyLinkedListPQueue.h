/*******************************************************
 * File: DoublyLinkedListPriorityQueue.h
 *
 * A priority queue class backed by an unsorted, doubly-linked
 * list.
 *
 * TODO: Answer the following questions:
 * What is the best-case runtime, in big-O notation, of inserting an
 * element into this priority queue? What is the worst-case runtime?
 *
 * ---> ANS: O(1) of Inserting
 *
 * What is the best-case runtime, in big-O notation, of removing an element
 * from this priority queue?  What is the worst-case runtime?
 *
 * ---> ANS: O(n) of Removing
 *
 * You can sort a sequence of elements by inserting them all into a priority
 * queue, then removing them one at a time. If you use this priority queue,
 * you will end up with a well-known sorting algorithm. What sorting
 * algorithm is it?
 *
 * ---> ANS: It's like Selection Sort Algorithm
 */
#ifndef PQueue_DoublyLinkedList_Included
#define PQueue_DoublyLinkedList_Included

#include <string>

/* A class representing a priority queue backed by an unsorted,
 * doubly-linked list.
 */
class DoublyLinkedListPriorityQueue {
public:
    /**
     * Constructs a new, empty priority queue.
     */
	DoublyLinkedListPriorityQueue();
	
    /**
     * Deallocates all memory allocated by this priority queue.
     */
	~DoublyLinkedListPriorityQueue();
	
    /**
     * Returns the number of elements stored in the priority queue.
     *
     * @return The number of elements stored in the priority queue.
     */
    int size() const;
	
    /**
     * Returns whether the queue is empty.
     *
     * @return Whether the queue is empty.
     */
    bool isEmpty() const;
	
    /**
     * Adds a new element to the priority queue.
     *
     * @param value The element to add
     */
    void enqueue(const std::string& value);
	
    /**
     * Returns, but does not remove, the lexicographically first string in
     * the priority queue. Equivalently, returns the next string that would
     * be removed by a call to dequeue.
     * <p>
     * If the priority queue is empty, this function will raise an error.
     *
     * @return The next string that would be dequeued.
     * @throws ErrorException If the queue is empty.
	 */
    std::string peek() const;
	
    /**
     * Returns and removes the lexicographically first string in the
     * priority queue.
     * <p>
     * If the priority queue is empty, this function will raise an error.
     *
     * @return The lexicographically first string in the queue.
     * @throws ErrorException If the queue is empty.
	 */
    std::string dequeueMin();

private:
    // TODO: Fill this in with your implementation of this class. Feel
    // free to add as many member functions, data members, structs,
    // and classes as you feel are necessary. Then, delete this comment.
    struct Cell {
        std::string value;
        Cell* previous;
        Cell* next;
    };

    Cell* first;

    int numElems = 0;
};

#endif
