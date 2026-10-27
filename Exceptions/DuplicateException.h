#ifndef DUPLICATE_EXCEPTION_H
#define DUPLICATE_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class DuplicateException : public runtime_error {
public:
    DuplicateException(const string& msg) : runtime_error("Дубликат: " + msg) {}
};

class DuplicateBookException : public DuplicateException {
public:
    DuplicateBookException(const string& msg) : DuplicateException("издание уже существует (" + msg + ")") {}
};

class DuplicateReaderException : public DuplicateException {
public:
    DuplicateReaderException(const string& name) : DuplicateException("читатель \"" + name + "\" уже зарегистрирован") {}
};

#endif