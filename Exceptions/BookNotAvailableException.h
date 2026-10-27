#ifndef BOOK_NOT_AVAILABLE_EXCEPTION_H
#define BOOK_NOT_AVAILABLE_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class BookNotAvailableException : public logic_error {
public:
    BookNotAvailableException() : logic_error("Ошибка операции: издание уже выдано другому читателю") {}
};

#endif