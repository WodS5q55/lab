#include "Book.h"
#include "Reader.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Book::Book() {
    id = 0;
    title = "";
    author = "";
    year = 0;
    type = "";
    borrowed_by = nullptr;
}

Book::Book(int book_id, string book_title, string book_author, int pub_year, string book_type) {
    validate_book_fields(book_title, book_author, pub_year, book_type);

    id = book_id;
    title = book_title;
    author = book_author;
    year = pub_year;
    type = book_type;
    borrowed_by = nullptr;
}

int Book::get_id() const { return id; }
string Book::get_title() const { return title; }
string Book::get_author() const { return author; }
int Book::get_year() const { return year; }
string Book::get_type() const { return type; }
Reader* Book::get_borrowed_by() const { return borrowed_by; }

bool Book::is_available() const { return borrowed_by == nullptr; }
bool Book::is_borrowed() const { return borrowed_by != nullptr; }

void Book::borrow_book(Reader* reader) {
    if (is_borrowed()) {
        throw BookNotAvailableException();
    }
    borrowed_by = reader;
}

void Book::return_book() {
    if (is_available()) {
        throw BookNotBorrowedException();
    }
    borrowed_by = nullptr;
}

string Book::short_line() const {
    string status = is_available() ? "Доступна" : "Выдана";
    return "#" + to_string(id) + " " + title + " - " + author + " [" + type + "] - " + status;
}

void Book::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "КНИГА (ID: " << id << ")" << endl;
    cout << "Название: " << title << endl;
    cout << "Автор: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Тип: " << type << endl;
    cout << "Статус: " << (is_available() ? "Доступна" : "Выдана") << endl;
    if (is_borrowed()) {
        cout << "Выдана читателю: " << borrowed_by->get_name() << endl;
    }
    cout << "-------------------------------------------" << endl;
}

bool Book::operator<(const Book& other) const {
    return id < other.id;
}

bool Book::operator>(const Book& other) const {
    return id > other.id;
}

bool Book::operator==(const Book& other) const {
    return year == other.year;
}

bool Book::operator!=(const Book& other) const {
    return year != other.year;
}

bool Book::operator<=(const Book& other) const {
    return year <= other.year;
}

bool Book::operator>=(const Book& other) const {
    return year >= other.year;
}

ostream& operator<<(ostream& os, const Book& book) {
    os << "Book#" << book.id
        << " \"" << book.title << "\" - " << book.author
        << " (" << book.year << ") [" << book.type << "] "
        << (book.is_available() ? "Доступна" : "Выдана");
    return os;
}

istream& operator>>(istream& is, Book& book) {
    cout << "ID книги: ";
    is >> book.id;
    is.ignore();

    cout << "Название: ";
    getline(is, book.title);

    cout << "Автор: ";
    getline(is, book.author);

    cout << "Год издания: ";
    is >> book.year;
    is.ignore();

    cout << "\nТип книги:" << endl;
    cout << "  1. учебник" << endl;
    cout << "  2. методическое пособие" << endl;
    cout << "  3. монография" << endl;
    cout << "Выберите (1-3): ";

    int type_choice;
    is >> type_choice;
    is.ignore();

    if (type_choice == 1) {
        book.type = "учебник";
    }
    else if (type_choice == 2) {
        book.type = "методическое пособие";
    }
    else if (type_choice == 3) {
        book.type = "монография";
    }
    else {
        throw InvalidBookTypeException("неверный выбор");
    }

    validate_book_fields(book.title, book.author, book.year, book.type);

    book.borrowed_by = nullptr;
    return is;
}