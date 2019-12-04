/******************************************************
 * File: RandomBag.h
 *
 * A class representing a bag of elements in which
 * values can be added and then removed randomly.
 */
#ifndef RandomBag_Included
#define RandomBag_Included

#include "vector.h"

class RandomBag {
public:
    void add(int value);
    int removeRandom();

    int size() const;
    bool isEmpty() const;

private:
    Vector<int> elems;
};

#endif
