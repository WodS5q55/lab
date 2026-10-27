#ifndef INVALID_PHONE_EXCEPTION_H
#define INVALID_PHONE_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class InvalidPhoneException : public invalid_argument {
public:
    InvalidPhoneException() : invalid_argument("Некорректные данные: номер телефона слишком короткий") {}
};

#endif