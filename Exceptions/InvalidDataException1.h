
#ifndef INVALID_DATA_EXCEPTION_H
#define INVALID_DATA_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidDataException : public invalid_argument {
public:
    InvalidDataException(const string& msg) : invalid_argument("Некорректные данные: " + msg) {}
};

class InvalidYearException : public InvalidDataException {
public:
    InvalidYearException(int year) : InvalidDataException("недопустимый год (" + to_string(year) + ")") {}
};

class InvalidPhoneException : public InvalidDataException {
public:
    InvalidPhoneException() : InvalidDataException("номер телефона слишком короткий") {}
};

class InvalidDateException : public InvalidDataException {
public:
    InvalidDateException() : InvalidDataException("неверный формат даты (дд.мм.гггг)") {}
};

#endif