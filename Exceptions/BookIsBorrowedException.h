#ifndef BOOK_IS_BORROWED_EXCEPTION_H
#define BOOK_IS_BORROWED_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class BookIsBorrowedException : public logic_error {
public:
    BookIsBorrowedException(const string& title) : logic_error("Ошибка операции: нельзя удалить выданное издание \"" + title + "\"") {}
};

#endif