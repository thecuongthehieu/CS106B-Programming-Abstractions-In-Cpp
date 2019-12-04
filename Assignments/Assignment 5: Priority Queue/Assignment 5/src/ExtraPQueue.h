/**********************************************
 * File: ExtraPQueue.h
 *
 * Your own custom priority queue class, if you
 * want to build one for extra credit.
 *
 * Please replace these file comments with a
 * description of how your priority queue works.
 */
#ifndef PQueue_Extra_Included
#define PQueue_Extra_Included

#include <string>

/*
 * TODO: Describe this class!
 */
class ExtraPriorityQueue {
public:
    /**
     * Constructs a new, empty priority queue.
     */
    ExtraPriorityQueue();

    /**
     * Deallocates all memory allocated by this priority queue.
     */
    ~ExtraPriorityQueue();

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
};

#endif
