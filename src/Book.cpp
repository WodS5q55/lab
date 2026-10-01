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

    if (book_pages < 1 || book_pages > 1000) {
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

string Book::get_type() const {
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
    cout << "Статус: " << (is_available() ? "Доступна" : "Выдана") << endl;
    if (is_borrowed()) {
        cout << "Выдана читателю: " << borrowed_by->get_name() << endl;
    }
    cout << "-------------------------------------------" << endl;
}

int Book::get_specific_value() const { return pages; }
string Book::get_specific_field() const { return type; }
string Book::get_specific_field_name() const { return "Тип"; }