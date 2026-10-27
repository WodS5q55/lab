#ifndef DUPLICATE_READER_EXCEPTION_H
#define DUPLICATE_READER_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class DuplicateReaderException : public runtime_error {
public:
    DuplicateReaderException(const string& name) : runtime_error("Дубликат читателя: \"" + name + "\" уже существует") {}
};

#endif