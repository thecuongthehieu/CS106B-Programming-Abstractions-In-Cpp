#include "OurHashSet.h"
#include "hashset.h" // For the hash functions
using namespace std;

const int kDefaultSize = 6; // Or really anything, really.

OurHashSet::OurHashSet() {
    /* Create a bunch of buckets! */
    for (int i = 0; i < kDefaultSize; i++) {
        buckets.add({}); // Add a new, empty bucket
    }
}

bool OurHashSet::contains(const string& value) const {
    /* Determine the bucket to jump into. */
    int bucket = hashCode(value) % buckets.size();

    /* Jump to that bucket. */
    for (string elem: buckets[bucket]) {
        if (elem == value) return true;
    }

    return false;
}

void OurHashSet::add(const string& value) {
    /* Determine the bucket to jump into. */
    int bucket = hashCode(value) % buckets.size();

    /* If this element is already present, we don't need to do anything. */
    for (string elem: buckets[bucket]) {
        if (elem == value) return;
    }

    buckets[bucket] += value;
    numElems++;
}

int OurHashSet::size() const {
    return numElems;
}

bool OurHashSet::isEmpty() const {
    return size() == 0;
}
