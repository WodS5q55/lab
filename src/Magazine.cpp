#include "Magazine.h"
#include "Reader.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

Magazine::Magazine() : Publication(0, "—", "—", 2020, 1) {
    issue_number = 1;
}

Magazine::Magazine(int mag_id, string mag_title, string mag_author, int pub_year, int mag_pages, int issue)
    : Publication(mag_id, mag_title, mag_author, pub_year, mag_pages) {

    if (mag_pages < 1 || mag_pages > 500) {
        throw InvalidBookDataException("журнал: страниц должно быть от 1 до 500");
    }

    if (issue < 1) {
        throw InvalidBookDataException("номер выпуска должен быть положительным");
    }
    issue_number = issue;
}

int Magazine::get_issue_number() const { return issue_number; }

void Magazine::set_issue_number(int new_issue) {
    if (new_issue < 1) {
        throw InvalidBookDataException("номер выпуска должен быть положительным");
    }
    issue_number = new_issue;
}

bool Magazine::is_latest_issue(int current_issue) const {
    return issue_number == current_issue;
}

bool Magazine::is_recent() const {
    int current_year = 2026;
    return (current_year - year) <= 1;
}

string Magazine::get_type() const {
    return "Журнал";
}

string Magazine::short_line() const {
    string status = is_available() ? "Доступна" : "Выдана";
    return "#" + to_string(id) + " [Журнал] " + title + " (выпуск " + to_string(issue_number) + ") - "
        + author + " - " + status;
}

void Magazine::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "ЖУРНАЛ (ID: " << id << ")" << endl;
    cout << "Название: " << title << endl;
    cout << "Издательство: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Страниц: " << pages << endl;
    cout << "Номер выпуска: " << issue_number << endl;
    cout << "Стоимость: " << calculate_price() << " руб." << endl;
    cout << "Статус: " << (is_available() ? "Доступна" : "Выдана") << endl;
    if (is_borrowed()) {
        cout << "Выдана читателю: " << borrowed_by->get_name() << endl;
    }
    cout << "-------------------------------------------" << endl;
}

double Magazine::calculate_price() const {
    double base_price = 5;
    double issue_cost = issue_number * 0.3;
    double pages_cost = pages * 0.1;

    return base_price + issue_cost + pages_cost;
}

string Magazine::get_specific_field() const { return to_string(issue_number); }
string Magazine::get_specific_field_name() const { return "Номер выпуска"; }