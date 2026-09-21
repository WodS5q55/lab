#include "Book.h"
#include "Reader.h" 
#include <iostream>
#include <stdexcept>

using namespace std;

Book::Book(string book_title, string book_author, int pub_year, string book_type) {
    if (book_title.empty() || book_author.empty()) {
        throw invalid_argument("Название и автор книги не могут быть пустыми");
    }
    if (pub_year < 1452 || pub_year > 2026) {
        throw invalid_argument("Некорректный год издания");
    }
    if (book_type != "учебник" && book_type != "методическое пособие" && book_type != "монография") {
        throw invalid_argument("Тип книги должен быть: учебник, методическое пособие или монография");
    }

    title = book_title;
    author = book_author;
    year = pub_year;
    type = book_type;
    borrowed_by = nullptr;  
}

string Book::get_title() const { return title; }
string Book::get_author() const { return author; }
int Book::get_year() const { return year; }
string Book::get_type() const { return type; }

Reader* Book::get_borrowed_by() const {
    return borrowed_by;
}

bool Book::is_available() const {
    return borrowed_by == nullptr;
}

bool Book::is_borrowed() const {
    return borrowed_by != nullptr;
}

void Book::borrow_book(Reader* reader) {
    if (is_borrowed()) {
        throw logic_error("Книга недоступна для выдачи");
    }
    borrowed_by = reader;  
}

void Book::return_book() {
    if (is_available()) {
        throw logic_error("Книга не была выдана");
    }
    borrowed_by = nullptr;
}

string Book::short_line() const {
    string status = is_available() ? "Доступна" : "Выдана";
    return title + " - " + author + " [" + type + "] - " + status;
}

void Book::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "КНИГА" << endl;
    cout << "Название: " << title << endl;
    cout << "Автор: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Тип: " << type << endl;
    cout << "Статус: " << (is_available() ? "Доступна" : "Выдана") << endl;

    if (is_borrowed()) {
        cout << "Выдана читателю: " << borrowed_by->get_name()
            << " (ID: " << borrowed_by->get_id() << ")" << endl;  
    }
    cout << "-------------------------------------------" << endl;
}