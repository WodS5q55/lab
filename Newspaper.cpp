#include "Newspaper.h"
#include "Reader.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

Newspaper::Newspaper() : Publication(0, "—", "—", 2020, 1) {
    publication_date = "01.01.2020";
}

Newspaper::Newspaper(int np_id, string np_title, string np_author, int pub_year, int np_pages, string date)
    : Publication(np_id, np_title, np_author, pub_year, np_pages) {

    if (date.empty()) {
        throw InvalidBookDataException("дата выпуска пустая");
    }
    publication_date = date;
}

string Newspaper::get_publication_date() const { return publication_date; }

void Newspaper::set_publication_date(string new_date) {
    if (new_date.empty()) {
        throw InvalidBookDataException("дата выпуска пустая");
    }
    publication_date = new_date;
}

string Newspaper::get_type() const {
    return "Газета";
}

string Newspaper::short_line() const {
    string status = is_available() ? "Доступна" : "Выдана";
    return "#" + to_string(id) + " [Газета] " + title + " (" + publication_date + ") - "
        + author + " - " + status;
}

void Newspaper::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "ГАЗЕТА (ID: " << id << ")" << endl;
    cout << "Название: " << title << endl;
    cout << "Издательство: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Страниц: " << pages << endl;
    cout << "Дата выпуска: " << publication_date << endl;
    cout << "Статус: " << (is_available() ? "Доступна" : "Выдана") << endl;
    if (is_borrowed()) {
        cout << "Выдана читателю: " << borrowed_by->get_name() << endl;
    }
    cout << "-------------------------------------------" << endl;
}

int Newspaper::get_specific_value() const { return year; }
string Newspaper::get_specific_field() const { return publication_date; }
string Newspaper::get_specific_field_name() const { return "Дата выпуска"; }