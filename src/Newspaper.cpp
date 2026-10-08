#include "Newspaper.h"
#include "Reader.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Newspaper::Newspaper() : Publication(0, "—", "—", 2020, 1) {
    publication_date = "01.01.2020";
}

Newspaper::Newspaper(int np_id, string np_title, string np_author, int np_pages, string date)
    : Publication(np_id, np_title, np_author, 2020, np_pages) {

    if (!is_valid_date(date)) {
        throw InvalidBookDataException("некорректная дата выпуска (формат: дд.мм.гггг)");
    }

    if (np_pages < 1 || np_pages > 96) {
        throw InvalidBookDataException("газета: страниц должно быть от 1 до 96");
    }

    publication_date = date;
    year = stoi(date.substr(6, 4));
}

string Newspaper::get_publication_date() const {
    return publication_date;
}

void Newspaper::set_publication_date(string new_date) {
    if (!is_valid_date(new_date)) {
        throw InvalidBookDataException("некорректная дата выпуска");
    }
    publication_date = new_date;
    year = stoi(new_date.substr(6, 4));
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
    cout << "Стоимость: " << calculate_price() << " руб." << endl;
    cout << "Статус: " << (is_available() ? "Доступна" : "Выдана") << endl;
    if (is_borrowed()) {
        cout << "Выдана читателю: " << borrowed_by->get_name() << endl;
    }
    cout << "-------------------------------------------" << endl;
}

double Newspaper::calculate_price() const {
    double base_price = 1.0;
    double pages_cost = pages * 0.5;

    return base_price + pages_cost;
}

string Newspaper::get_field() const {
    return publication_date;
}

string Newspaper::get_field_name() const {
    return "Дата выпуска";
}