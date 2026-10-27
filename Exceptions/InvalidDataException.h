#ifndef INVALID_DATA_EXCEPTION_H
#define INVALID_DATA_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidDataException : public invalid_argument {
public:
    InvalidDataException(const string& msg) : invalid_argument("Некорректные данные: " + msg) {}
};

#endif