#include "Reader.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

int Reader::next_id = 1;

Reader::Reader() {
    full_name = "";
    phone = "";
    reader_id = 0;
}

Reader::Reader(string name, string phone_num) {
    if (name.empty()) {
        throw InvalidReaderNameException();
    }
    if (phone_num.length() < 5) {
        throw InvalidPhoneException();
    }
    full_name = name;
    phone = phone_num;
    reader_id = next_id++;
}

string Reader::get_name() const { return full_name; }
string Reader::get_phone() const { return phone; }
int Reader::get_id() const { return reader_id; }

void Reader::set_name(string new_name) {
    if (new_name.empty()) {
        throw InvalidReaderNameException();
    }
    full_name = new_name;
}

void Reader::set_phone(string new_phone) {
    if (new_phone.length() < 5) {
        throw InvalidPhoneException();
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

bool Reader::operator<(const Reader& other) const {
    return reader_id < other.reader_id;
}

bool Reader::operator>(const Reader& other) const {
    return reader_id > other.reader_id;
}

bool Reader::operator==(const Reader& other) const {
    return full_name == other.full_name;
}

bool Reader::operator!=(const Reader& other) const {
    return full_name != other.full_name;
}

bool Reader::operator<=(const Reader& other) const {
    return full_name <= other.full_name;
}

bool Reader::operator>=(const Reader& other) const {
    return full_name >= other.full_name;
}

ostream& operator<<(ostream& os, const Reader& reader) {
    os << "Reader#" << reader.reader_id
        << ": " << reader.full_name
        << " (тел.: " << reader.phone << ")";
    return os;
}

istream& operator>>(istream& is, Reader& reader) {
    cout << "ФИО: ";
    getline(is, reader.full_name);

    cout << "Телефон: ";
    getline(is, reader.phone);

    if (reader.full_name.empty()) {
        throw InvalidReaderNameException();
    }
    if (reader.phone.length() < 5) {
        throw InvalidPhoneException();
    }

    reader.reader_id = Reader::next_id++;
    return is;
}