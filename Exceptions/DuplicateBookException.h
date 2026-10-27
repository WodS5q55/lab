#ifndef DUPLICATE_BOOK_EXCEPTION_H
#define DUPLICATE_BOOK_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class DuplicateBookException : public runtime_error {
public:
    DuplicateBookException(const string& msg) : runtime_error("Дубликат издания: " + msg) {}
};

#endif