#include "Book.h"
#include <iostream>
#include <stdexcept>

using namespace std;

string status_to_string(BookStatus status) {
    return (status == AVAILABLE) ? "Доступна" : "Выдана";
}

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
    status = AVAILABLE;
    borrowed_by = -1;
}

string Book::get_title() const { return title; }
string Book::get_author() const { return author; }
int Book::get_year() const { return year; }
string Book::get_type() const { return type; }
BookStatus Book::get_status() const { return status; }
int Book::get_borrowed_by() const { return borrowed_by; }

void Book::borrow_book(int reader_id) {
    if (status != AVAILABLE) {
        throw logic_error("Книга недоступна для выдачи");
    }
    status = BORROWED;
    borrowed_by = reader_id;
}

void Book::return_book() {
    if (status != BORROWED) {
        throw logic_error("Книга не была выдана");
    }
    status = AVAILABLE;
    borrowed_by = -1;
}

string Book::short_line() const {
    return title + " - " + author + " [" + type + "] - " + status_to_string(status);
}

void Book::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "КНИГА" << endl;
    cout << "Название: " << title << endl;
    cout << "Автор: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Тип: " << type << endl;
    cout << "Статус: " << status_to_string(status) << endl;
    cout << "-------------------------------------------" << endl;
}