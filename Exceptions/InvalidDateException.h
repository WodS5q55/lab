#ifndef INVALID_DATE_EXCEPTION_H
#define INVALID_DATE_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class InvalidDateException : public invalid_argument {
public:
    InvalidDateException() : invalid_argument("Некорректные данные: неверный формат даты (дд.мм.гггг)") {}
};

#endif