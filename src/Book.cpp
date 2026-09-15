#include "Book.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;

// Срок выдачи — 14 дней
const int MAX_BORROW_DAYS = 14;

string status_to_string(BookStatus status) {
    return (status == AVAILABLE) ? "Доступна" : "Выдана";
}

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
    borrow_date = 0;
}

string Book::get_title() const { return title; }
string Book::get_author() const { return author; }
int Book::get_year() const { return year; }
string Book::get_type() const { return type; }
BookStatus Book::get_status() const { return status; }
int Book::get_borrowed_by() const { return borrowed_by; }
time_t Book::get_borrow_date() const { return borrow_date; }

int Book::get_days_left() const {
    if (status != BORROWED || borrow_date == 0) return 0;

    // Дата возврата = дата выдачи + 14 дней
    time_t due_date = borrow_date + (MAX_BORROW_DAYS * 24 * 60 * 60);

    // Сколько секунд осталось до этой даты
    time_t now = time(0);
    double seconds_left = difftime(due_date, now);

    // Переводим в дни
    return static_cast<int>(seconds_left / (24 * 60 * 60));
}

bool Book::is_overdue() const {
    if (status != BORROWED) return false;
    return get_days_left() < 0;
}

void Book::borrow_book(int reader_id) {
    if (status != AVAILABLE) {
        throw logic_error("Книга недоступна для выдачи");
    }
    status = BORROWED;
    borrowed_by = reader_id;
    borrow_date = time(0);   // ← запоминаем дату выдачи
}

void Book::return_book() {
    if (status != BORROWED) {
        throw logic_error("Книга не была выдана");
    }
    status = AVAILABLE;
    borrowed_by = -1;
    borrow_date = 0;
}

string Book::short_line() const {
    string line = title + " - " + author + " [" + type + "] - ";

    if (status == AVAILABLE) {
        line += "Доступна";
    }
    else {
        int days = get_days_left();
        if (days > 0) {
            line += "Выдана (осталось " + to_string(days) + " дн.)";
        }
        else if (days == 0) {
            line += "Выдана (последний день)";
        }
        else {
            line += "ПРОСРОЧЕНА на " + to_string(-days) + " дн.!";
        }
    }
    return line;
}

void Book::display_info() const {
    cout << "-------------------------------------------" << endl;
    cout << "КНИГА" << endl;
    cout << "Название: " << title << endl;
    cout << "Автор: " << author << endl;
    cout << "Год издания: " << year << endl;
    cout << "Тип: " << type << endl;
    cout << "Статус: " << status_to_string(status) << endl;

    if (status == BORROWED) {
        cout << "Выдана читателю ID: " << borrowed_by << endl;

        // Форматируем дату выдачи
        tm ltm;
        localtime_s(&ltm, &borrow_date);

        char buffer[11];
        strftime(buffer, 11, "%d.%m.%Y", &ltm);
        cout << "Дата выдачи: " << buffer << endl;

        // Срок возврата
        time_t due = borrow_date + (MAX_BORROW_DAYS * 24 * 60 * 60);
        localtime_s(&ltm, &due);
        strftime(buffer, 11, "%d.%m.%Y", &ltm);
        cout << "Срок возврата: " << buffer << endl;

        // Осталось / просрочено
        int days = get_days_left();
        if (days > 0) {
            cout << "Осталось дней: " << days << endl;
        }
        else if (days == 0) {
            cout << "Последний день возврата!" << endl;
        }
        else {
            cout << "[ВНИМАНИЕ] Просрочена на " << -days << " дн.!" << endl;
        }
    }
    cout << "-------------------------------------------" << endl;
}