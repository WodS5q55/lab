#ifndef INDEX_OUT_OF_RANGE_EXCEPTION_H
#define INDEX_OUT_OF_RANGE_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class IndexOutOfRangeException : public out_of_range {
public:
    IndexOutOfRangeException(size_t index, size_t size)
        : out_of_range("Индекс " + to_string(index) +
            " выходит за пределы коллекции (размер: " + to_string(size) + ")") {}

};

#endif