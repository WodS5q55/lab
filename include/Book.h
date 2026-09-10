#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

enum BookStatus {
    AVAILABLE,
    BORROWED
};

string status_to_string(BookStatus status, int days_left);

class Book {
private:
    string title;
    string author;
    int year;
    string type;
    BookStatus status;
    int borrowed_by;
    int days_left;

public:
    Book(string book_title, string book_author, int pub_year, string book_type);

    string get_title() const;
    string get_author() const;
    int get_year() const;
    string get_type() const;
    BookStatus get_status() const;
    int get_borrowed_by() const;
    int get_days_left() const;

    void borrow_book(int reader_id, int days = 14);
    void return_book();
    void decrease_days();
    bool is_overdue() const;
    string short_line() const;
    void display_info() const;
};

#endif