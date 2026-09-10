#include "Book.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Book::Book(string book_title, string book_author, int pub_year, string book_type) {
    if (book_title.empty() || book_author.empty()) {
        throw invalid_argument("Название и автор книги не могут быть пустыми");
    }
    if (pub_year < 0 || pub_year > 2026) {
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
    days_left = 0;
}

string status_to_string(BookStatus status, int days_left) {
    switch (status) {
    case AVAILABLE:
        return "Доступна";
    case BORROWED:
        if (days_left > 0) {
            return "Выдана (осталось " + to_string(days_left) + " дн.)";
        }
        return "Выдана ПРОСРОЧЕНА!";
    }
    return "Неизвестно";
}

string Book::get_title() const { return title; }
string Book::get_author() const { return author; }
int Book::get_year() const { return year; }
string Book::get_type() const { return type; }
BookStatus Book::get_status() const { return status; }
int Book::get_borrowed_by() const { return borrowed_by; }
int Book::get_days_left() const { return days_left; }

void Book::borrow_book(int reader_id, int days) {
    if (status != AVAILABLE) {
        throw logic_error("Книга недоступна для выдачи");
    }
    status = BORROWED;
    borrowed_by = reader_id;
    days_left = days;
}

void Book::return_book() {
    if (status != BORROWED) {
        throw logic_error("Книга не была выдана");
    }
    status = AVAILABLE;
    borrowed_by = -1;
    days_left = 0;
}

void Book::decrease_days() {
    if (status == BORROWED && days_left > 0) {
        days_left--;
    }
}

bool Book::is_overdue() const {
    return (status == BORROWED && days_left <= 0);
}

string Book::short_line() const {
    return title + " - " + author + " [" + type + "] - " + status_to_string(status, days_left);
}

void Book::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "КНИГА" << endl;
    cout << "Название: " << title << endl;
    cout << "Автор: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Тип: " << type << endl;
    cout << "Статус: " << status_to_string(status, days_left) << endl;
    if (status == BORROWED) {
        cout << "Выдана читателю ID: " << borrowed_by << endl;
        if (is_overdue()) {
            cout << "[ВНИМАНИЕ] КНИГА ПРОСРОЧЕНА!" << endl;
        }
    }
    cout << "-------------------------------------------" << endl;
}