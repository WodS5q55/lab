#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

using namespace std;

class Reader;

class Book {
private:
    int id;
    string title;
    string author;
    int year;
    int pages;
    string type;
    Reader* borrowed_by;

public:
    Book();
    Book(int book_id, string book_title, string book_author, int pub_year, int book_pages, string book_type);

    int get_id() const;
    string get_title() const;
    string get_author() const;
    int get_year() const;
    int get_pages() const;
    string get_type() const;
    Reader* get_borrowed_by() const;

    bool is_available() const;
    bool is_borrowed() const;

    void borrow_book(Reader* reader);
    void return_book();

    string short_line() const;
    void display_info() const;

    bool operator<(const Book& other) const;
    bool operator>(const Book& other) const;

    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
    bool operator<=(const Book& other) const;
    bool operator>=(const Book& other) const;

    friend ostream& operator<<(ostream& os, const Book& book);
    friend istream& operator>>(istream& is, Book& book);
};

#endif