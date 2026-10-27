#ifndef INVALID_YEAR_EXCEPTION_H
#define INVALID_YEAR_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class InvalidYearException : public invalid_argument {
public:
    InvalidYearException(int year) : invalid_argument("Некорректные данные: недопустимый год (" + to_string(year) + ")") {}
};

#endif