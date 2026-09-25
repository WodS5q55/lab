#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidBookDataException : public invalid_argument {
public:
    InvalidBookDataException(const string& message)
        : invalid_argument("Некорректные данные книги: " + message) {}
};

class InvalidYearException : public invalid_argument {
public:
    InvalidYearException(int year)
        : invalid_argument("Некорректный год издания: " + to_string(year)) {}
};

class InvalidBookTypeException : public invalid_argument {
public:
    InvalidBookTypeException(const string& type)
        : invalid_argument("Некорректный тип книги: " + type) {}
};

class BookNotAvailableException : public logic_error {
public:
    BookNotAvailableException()
        : logic_error("Книга недоступна для выдачи") {}
};

class BookNotBorrowedException : public logic_error {
public:
    BookNotBorrowedException()
        : logic_error("Книга не была выдана") {}
};

class BookIsBorrowedException : public logic_error {
public:
    BookIsBorrowedException(const string& title)
        : logic_error("Нельзя удалить выданную книгу: \"" + title + "\"") {}
};

class DuplicateBookException : public invalid_argument {
public:
    DuplicateBookException(const string& message)
        : invalid_argument("Книга уже существует: " + message) {}
};

class BookNotFoundException : public invalid_argument {
public:
    BookNotFoundException()
        : invalid_argument("Книга не найдена") {}
};

class InvalidReaderNameException : public invalid_argument {
public:
    InvalidReaderNameException()
        : invalid_argument("Имя читателя не может быть пустым") {}
};

class InvalidPhoneException : public invalid_argument {
public:
    InvalidPhoneException()
        : invalid_argument("Номер телефона слишком короткий (минимум 5 символов)") {}
};

class DuplicateReaderException : public invalid_argument {
public:
    DuplicateReaderException(const string& name)
        : invalid_argument("Читатель с именем \"" + name + "\" уже зарегистрирован") {}
};

class ReaderNotFoundException : public invalid_argument {
public:
    ReaderNotFoundException()
        : invalid_argument("Читатель не найден") {}
};

class BorrowException : public runtime_error {
public:
    BorrowException(const string& message)
        : runtime_error("Ошибка выдачи: " + message) {}
};

class ReturnException : public runtime_error {
public:
    ReturnException(const string& message)
        : runtime_error("Ошибка возврата: " + message) {}
};

#endif