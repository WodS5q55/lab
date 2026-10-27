#ifndef OPERATION_EXCEPTION_H
#define OPERATION_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class OperationException : public logic_error {
public:
    OperationException(const string& msg) : logic_error("Ошибка операции: " + msg) {}
};

class BookIsBorrowedException : public OperationException {
public:
    BookIsBorrowedException(const string& title) : OperationException("нельзя удалить выданное издание \"" + title + "\"") {}
};

class BookNotAvailableException : public OperationException {
public:
    BookNotAvailableException() : OperationException("издание уже выдано другому читателю") {}
};

#endif