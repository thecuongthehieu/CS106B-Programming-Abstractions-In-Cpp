#ifndef OurHashSet_Included
#define OurHashSet_Included

#include <string>
#include "vector.h"

class OurHashSet {
public:
    OurHashSet();

    bool contains(const std::string& value) const;
    void add(const std::string& value);

    int size() const;
    bool isEmpty() const;

private:
    Vector<Vector<std::string>> buckets;
    int numElems = 0;
};


#endif
