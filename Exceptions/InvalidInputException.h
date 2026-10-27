#ifndef INVALID_INPUT_EXCEPTION_H
#define INVALID_INPUT_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class InvalidInputException : public invalid_argument {
public:
    InvalidInputException(const string& msg) : invalid_argument("Некорректные данные: " + msg) {}
};

#endif