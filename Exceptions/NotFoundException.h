#ifndef NOT_FOUND_EXCEPTION_H
#define NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class NotFoundException : public runtime_error {
public:
    NotFoundException(const string& msg) : runtime_error("Не найдено: " + msg) {}
};

class BookNotFoundException : public NotFoundException {
public:
    BookNotFoundException() : NotFoundException("издание отсутствует в библиотеке") {}
};

class ReaderNotFoundException : public NotFoundException {
public:
    ReaderNotFoundException() : NotFoundException("читатель не найден") {}
};

#endif