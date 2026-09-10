#include "Reader.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int Reader::next_id = 1;

Reader::Reader(string name, string phone_num) {
    if (name.empty()) {
        throw invalid_argument("Имя читателя не может быть пустым");
    }
    full_name = name;
    phone = phone_num;
    reader_id = next_id++;
}

string Reader::get_name() const {
    return full_name;
}

string Reader::get_phone() const {
    return phone;
}

int Reader::get_id() const {
    return reader_id;
}

void Reader::set_phone(string new_phone) {
    if (new_phone.length() < 5) {
        throw invalid_argument("Номер телефона слишком короткий");
    }
    phone = new_phone;
}

void Reader::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "ЧИТАТЕЛЬ" << endl;
    cout << "ID: " << reader_id << endl;
    cout << "ФИО: " << full_name << endl;
    cout << "Телефон: " << phone << endl;
    cout << "-------------------------------------------" << endl;
}