#include "Book.h"
#include "Reader.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

Book::Book() : Publication(0, "—", "—", 2020, 1) {
    type = "учебник";
}

Book::Book(int book_id, string book_title, string book_author, int pub_year, int book_pages, string book_type)
    : Publication(book_id, book_title, book_author, pub_year, book_pages) {

    if (book_pages < 1 || book_pages > 10000) {
        throw InvalidBookDataException("книга: страниц должно быть от 1 до 10000");
    }

    if (book_type != "учебник" && book_type != "методическое пособие" && book_type != "монография") {
        throw InvalidBookTypeException(book_type);
    }
    type = book_type;
}

string Book::get_book_type() const { return type; }

void Book::set_book_type(string new_type) {
    if (new_type != "учебник" && new_type != "методическое пособие" && new_type != "монография") {
        throw InvalidBookTypeException(new_type);
    }
    type = new_type;
}

bool Book::is_for_students() const {
    return (type == "учебник" || type == "методическое пособие");
}

bool Book::is_too_old_for_study() const {
    int current_year = 2026;
    return (type == "учебник" && (current_year - year) > 10);
}

int Book::get_difficulty_level() const {
    if (type == "учебник") return 2;
    if (type == "методическое пособие") return 3;
    if (type == "монография") return 5;
    return 1;
}

string Book::get_type4() const {
    return "Книга";
}

string Book::short_line() const {
    string status = is_available() ? "Доступна" : "Выдана";
    return "#" + to_string(id) + " [Книга] " + title + " (" + to_string(pages) + " стр.) - "
        + author + " [" + type + "] - " + status;
}

void Book::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "КНИГА (ID: " << id << ")" << endl;
    cout << "Название: " << title << endl;
    cout << "Автор: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Страниц: " << pages << endl;
    cout << "Тип: " << type << endl;
    cout << "Стоимость: " << calculate_price() << " руб." << endl;
    cout << "Статус: " << (is_available() ? "Доступна" : "Выдана") << endl;
    if (is_borrowed()) {
        cout << "Выдана читателю: " << borrowed_by->get_name() << endl;
    }
    cout << "-------------------------------------------" << endl;
}

double Book::calculate_price() const {
    double price_per_page;

    if (type == "учебник") {
        price_per_page = 0.1;
    }
    else if (type == "методическое пособие") {
        price_per_page = 0.08;
    }
    else if (type == "монография") {
        price_per_page = 0.15;
    }
    else {
        price_per_page = 0.05;
    }

    return pages * price_per_page;
}

string Book:: get_field() const { return type; }
string Book::get_field_name() const { return "Тип"; }