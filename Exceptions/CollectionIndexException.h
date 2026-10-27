#ifndef COLLECTION_INDEX_EXCEPTION_H
#define COLLECTION_INDEX_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class CollectionIndexOutOfRangeException : public out_of_range {
public:
    CollectionIndexOutOfRangeException() : out_of_range("Индекс выходит за пределы коллекции") {}
};

#endif